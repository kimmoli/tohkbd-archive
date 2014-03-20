/*
 * (C) 2014 Kimmo Lindholm <kimmo.lindholm@gmail.com> Kimmoli
 *
 * Main, Daemon functions, logger
 *
 *
 *
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include "tohkbd.h"
#include "tohkeyboard.h"
#include "tca8424.h"
#include "toh.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtDBus/QtDBus>
#include <QDBusConnection>
#include <QDBusMessage>


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    daemonize();

    setlinebuf(stdout);
    setlinebuf(stderr);

    printf("Starting tohkbd daemon. build %s %s\n", __DATE__, __TIME__);

    if (!QDBusConnection::systemBus().isConnected())
    {
        printf("Cannot connect to the D-Bus systemBus\n%s\n",
               qPrintable(QDBusConnection::systemBus().lastError().message()));
        sleep(3);
        exit(EXIT_FAILURE);
    }
    printf("Connected to D-Bus systembus\n");

    if (!QDBusConnection::sessionBus().isConnected())
    {
        printf("Cannot connect to the D-Bus sessionBus\n%s\n",
               qPrintable(QDBusConnection::sessionBus().lastError().message()));
        sleep(3);
        exit(EXIT_FAILURE);
    }
    printf("Connected to D-Bus sessionbus\n");

    Tohkbd tohkbd;


    /* Nokia MCE display_status_ind
     * No actual use with this, just make log entry. Display status returns string: "on", "dimmed" or "off"  */

    static QDBusConnection mceSignalconn = QDBusConnection::systemBus();
    mceSignalconn.connect("com.nokia.mce", "/com/nokia/mce/signal", "com.nokia.mce.signal", "display_status_ind",
                          &tohkbd, SLOT(handleDisplayStatus(const QDBusMessage&)));

    if(mceSignalconn.isConnected())
    {
        printf("com.nokia.mce.signal.display_status_ind Connected\n");
    }
    else
    {
        printf("com.nokia.mce.signal.display_status_ind Not connected\n%s\n",
               qPrintable(QDBusConnection::systemBus().lastError().message()));
    }


    return app.exec();

}

void daemonize()
{
    /* Change the file mode mask */
    umask(0);

    /* Change the current working directory */
    if ((chdir("/tmp")) < 0)
        exit(EXIT_FAILURE);

    /* Close out the standard file descriptors */
    // close(STDIN_FILENO);
    // close(STDOUT_FILENO);
    // close(STDERR_FILENO);

    /* register signals to monitor / ignore */
    signal(SIGCHLD,SIG_IGN); /* ignore child */
    signal(SIGTSTP,SIG_IGN); /* ignore tty signals */
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGHUP,signalHandler); /* catch hangup signal */
    signal(SIGTERM,signalHandler); /* catch kill signal */
}


void signalHandler(int sig) /* signal handler function */
{
    switch(sig)
    {
        case SIGHUP:
            /* rehash the server */
            printf("Received signal SIGHUP\n");
            break;
        case SIGTERM:
            /* finalize the server */
            printf("Received signal SIGTERM\n");
            controlVdd(0);
            exit(0);
            break;
    }
}
