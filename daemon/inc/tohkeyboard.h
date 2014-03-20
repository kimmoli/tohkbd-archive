/*
 * (C) 2014 Kimmo Lindholm <kimmo.lindholm@gmail.com> Kimmoli
 *
 */

#ifndef TOHKEYBOARD_H
#define TOHKEYBOARD_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtDBus/QtDBus>

#include <QTime>
#include <QThread>
#include "worker.h"

#include "uinputif.h"


/* main class */

class Tohkbd: public QObject
{
    Q_OBJECT

public:
    Tohkbd();

    ~Tohkbd()
    {
        uinputif->closeUinputDevice();

        worker->abort();
        thread->wait();
        delete thread;
        delete worker;
    }

public slots:
    QString setVddState(const QString &arg);
    QString kill(const QString &arg);

    /* interrupts */
    QString setInterruptEnable(const QString &arg);
    void handleGpioInterrupt();
    void handleDisplayStatus(const QDBusMessage& msg);

private slots:
    void timerTimeout();


private:
    QThread *thread;
    Worker *worker;
    UinputIf *uinputif;

    static bool vddEnabled;
    static bool interruptsEnabled;

    static int capsLockSeq;

    int tca_led;
    QTimer *timer;

    QMutex mutex;

    int gpio_fd;
};



#endif // TOHKEYBOARD_H
