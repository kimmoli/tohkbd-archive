/*
 * (C) 2014 Kimmo Lindholm <kimmo.lindholm@gmail.com> Kimmoli
 *
 * toholed daemon, d-bus server call method functions.
 *
 *
 *
 *
 */

//#define TEST_NOHW 1

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtDBus/QtDBus>
#include <QDBusArgument>
#include <QTime>
#include <QThread>
//#include <QtDebug>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <poll.h>

#include "tohkeyboard.h"
#include "toh.h"
#include "tca8424.h"

#include "uinputif.h"
#include <linux/input.h>
#include <linux/uinput.h>


bool Tohkbd::interruptsEnabled = false;
bool Tohkbd::vddEnabled = false;

int Tohkbd::capsLockSeq = 0;

/* Main */
Tohkbd::Tohkbd()
{
    thread = new QThread();
    worker = new Worker();

    worker->moveToThread(thread);
    connect(worker, SIGNAL(gpioInterruptCaptured()), this, SLOT(handleGpioInterrupt()));
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);

    /* do this automatically at startup */
#ifndef TEST_NOHW
    setVddState("on");
    setInterruptEnable("on");
#endif

    uinputif = new UinputIf();
    uinputif->openUinputDevice();
}


/* Function to set VDD (3.3V for OH) */
QString Tohkbd::setVddState(const QString &arg)
{
    QString tmp = QString("VDD control request - turn %1 ").arg(arg);
    QString turn = QString("%1").arg(arg);
    QByteArray ba = tmp.toLocal8Bit();

    printf("%s\n", ba.data());

    if (controlVdd( ( QString::localeAwareCompare( turn, "on") ? 0 : 1) ) < 0)
    {
        vddEnabled = false;
        printf("VDD control FAILED\n");
    }
    else
    {
        vddEnabled = QString::localeAwareCompare( turn, "on") ? false : true;
        printf("VDD control OK\n");
    }

    return QString("you have been served. %1").arg(arg);
}


/* Kills toholed daemon */
QString Tohkbd::kill(const QString &arg)
{
    printf("Someone wants to kill me\n");
    QMetaObject::invokeMethod(QCoreApplication::instance(), "quit");

    return QString("AAARGH. %1").arg(arg);
}


/*
 *    Interrupt stuff
 */


QString Tohkbd::setInterruptEnable(const QString &arg)
{
    QString turn = QString("%1").arg(arg);
    int fd;

    if (!vddEnabled)
        return QString("VDD Not active. Aborting.");

    if(QString::localeAwareCompare( turn, "on") == 0)
    {
        printf("enabling interrupt\n");


        gpio_fd = getTohInterrupt();

        if (gpio_fd > -1)
        {
            worker->abort();
            thread->wait(); // If the thread is not running, this will immediately return.

            worker->requestWork(gpio_fd);

            printf("worker started\n");


            fd = tca8424_initComms(TCA_ADDR);
            if (fd<0)
            {
                printf("failed to start communication with TCA8424\n");
                return QString("failed");
            }
            tca8424_reset(fd);
            tca8424_closeComms(fd);


            interruptsEnabled = true;

            return QString("success");
        }
        else
        {
            printf("failed to enable interrupt (are you root?)\n");
            interruptsEnabled = false;
            return QString("failed");
        }
    }
    else
    {

        printf("disabling interrupt\n");

        interruptsEnabled = false;


        worker->abort();
        thread->wait();
/*
        delete thread;
        delete worker;
*/
        releaseTohInterrupt(gpio_fd);

        return QString("disabled");
    }

}

void Tohkbd::handleDisplayStatus(const QDBusMessage& msg)
{
    QList<QVariant> args = msg.arguments();

    printf("Display status changed to \"%s\"\n", qPrintable(args.at(0).toString()));

    QString turn = QString("%1").arg(args.at(0).toString());

    if ((QString::localeAwareCompare( turn, "on") == 0) && !vddEnabled && !interruptsEnabled)
    {
        printf("enabling tohkbd\n");
        setVddState("on");
        setInterruptEnable("on");
    }
    else if ((QString::localeAwareCompare( turn, "off") == 0) && vddEnabled && interruptsEnabled)
    {
        printf("disabling tohkbd\n");
        setInterruptEnable("off");
        setVddState("off");
    }

}



/*
 *  GPIO interrupt handler
 *
 */

void Tohkbd::handleGpioInterrupt()
{
    static int haveCtrl = 0;
    int fd, code, isShift, isAlt, isCtrl;
    char inRep[12];
    const char *buf;

    mutex.lock();

    fd = tca8424_initComms(TCA_ADDR);
    if (fd<0)
    {
        printf("failed to start communication with TCA8424\n");
        mutex.unlock();
        return;
    }
    tca8424_readInputReport(fd, inRep);

    buf = tca8424_processKeyMap(inRep, &code, &isShift, &isAlt, &isCtrl);

    if ((code != 0) && (capsLockSeq == 1 || capsLockSeq == 2)) /* Abort caps-lock if other key pressed */
        capsLockSeq = 0;

    if (code == 0 && isShift && capsLockSeq == 0) /* Shift pressed first time */
        capsLockSeq = 1;
    else if (code == 0 && buf[0]=='!' && capsLockSeq == 1) /* Shift released */
        capsLockSeq = 2;
    else if (code == 0 && isShift && capsLockSeq == 2) /* Shift pressed 2nd time */
    {
        capsLockSeq = 3;
        uinputif->sendUinputKeyPress(KEY_CAPSLOCK, 1);
        uinputif->sendUinputKeyPress(KEY_CAPSLOCK, 0);
        uinputif->synUinputDevice();
        tca8424_leds(fd, 1);
        printf("CapsLock on\n");
    }
    else if (code == 0 && isShift && capsLockSeq == 3) /* Shift pressed 3rd time */
    {
        capsLockSeq = 0;
        uinputif->sendUinputKeyPress(KEY_CAPSLOCK, 1);
        uinputif->sendUinputKeyPress(KEY_CAPSLOCK, 0);
        uinputif->synUinputDevice();
        tca8424_leds(fd, 0);
        printf("CapsLock off\n");
    }
    else if (code == 0 && isCtrl) /* Ctrl pressed */
    {
        haveCtrl ^= 1;
        uinputif->sendUinputKeyPress(KEY_LEFTCTRL, haveCtrl);
        printf("%s\n", haveCtrl ? "Ctrl down" : "Ctrl lifted");
    }

    if (code != 0) /* We resolved what was pressed */
    {
        printf("Key pressed: %s (%d 0x%02x shft=%d alt=%d ctrl=%d)\n",
               buf, code, inRep[5], isShift, isAlt, haveCtrl);

        if (isShift)
            uinputif->sendUinputKeyPress(KEY_LEFTSHIFT, 1);
        uinputif->sendUinputKeyPress(code, 1);
        uinputif->sendUinputKeyPress(code, 0);
        if (isShift)
            uinputif->sendUinputKeyPress(KEY_LEFTSHIFT, 0);
        if (haveCtrl)
        {
            uinputif->sendUinputKeyPress(KEY_LEFTCTRL, 0);
            printf("Ctrl released automatically\n");
            haveCtrl = 0;
        }

        uinputif->synUinputDevice();

    }
    else if (buf[0] != '!')
    {
        printf("UNK Input report: %s %02x%02x%02x%02x%02x %02x%02x%02x%02x%02x%02x\n",
               buf, inRep[0], inRep[1], inRep[2], inRep[3], inRep[4], inRep[5],
               inRep[6], inRep[7], inRep[8], inRep[9], inRep[10]);
    }

    tca8424_closeComms(fd);
    mutex.unlock();
}
