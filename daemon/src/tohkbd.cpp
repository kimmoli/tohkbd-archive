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
    char buf[100];

    QCoreApplication app(argc, argv);

    daemonize();

    snprintf(buf, 100, "Starting tohkbd daemon. build %s %s", __DATE__, __TIME__);
    writeToLog(buf);

    if (!QDBusConnection::systemBus().isConnected())
    {
        fprintf(stderr, "Cannot connect to the D-Bus systemBus\n");
        writeToLog("Cannot connect to the D-Bus systemBus");
        writeToLog(qPrintable(QDBusConnection::systemBus().lastError().message()));
        sleep(3);
        exit(EXIT_FAILURE);
    }
    writeToLog("Connected to D-Bus systembus");

    writeToLog(qPrintable(getenv ("DBUS_SESSION_BUS_ADDRESS")));

    if (!QDBusConnection::sessionBus().isConnected())
    {
        fprintf(stderr, "Cannot connect to the D-Bus sessionBus\n");
        writeToLog("Cannot connect to the D-Bus sessionBus");
        writeToLog(qPrintable(QDBusConnection::sessionBus().lastError().message()));
        sleep(3);
        exit(EXIT_FAILURE);
    }
    writeToLog("Connected to D-Bus sessionbus");

    Tohkbd tohkbd;


    /* Nokia MCE display_status_ind
     * No actual use with this, just make log entry. Display status returns string: "on", "dimmed" or "off"  */

    static QDBusConnection mceSignalconn = QDBusConnection::systemBus();
    mceSignalconn.connect("com.nokia.mce", "/com/nokia/mce/signal", "com.nokia.mce.signal", "display_status_ind",
                          &tohkbd, SLOT(handleDisplayStatus(const QDBusMessage&)));

    if(mceSignalconn.isConnected())
        writeToLog("com.nokia.mce.signal.display_status_ind Connected");
    else
    {
        writeToLog("com.nokia.mce.signal.display_status_ind Not connected");
        writeToLog(qPrintable(QDBusConnection::systemBus().lastError().message()));
    }


    return app.exec();

}


void writeToLog(const char *buf)
{
    int logFile;
    char ts[20];
    char tmp[1024];

    time_t t;
    struct tm *tnow;

    t = time(NULL);
    tnow = localtime(&t);

    strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", tnow);

    snprintf(tmp, sizeof(tmp), "%s :: %s\r\n", ts, buf);

    logFile = open("tohkbdlog", O_WRONLY | O_CREAT | O_APPEND, 0666);

    if (logFile != -1)
        write(logFile, tmp, strlen(tmp));

    close(logFile);
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
            writeToLog("Received signal SIGHUP");
            break;
        case SIGTERM:
            /* finalize the server */
            writeToLog("Received signal SIGTERM");
            controlVdd(0);
            exit(0);
            break;
    }
}
