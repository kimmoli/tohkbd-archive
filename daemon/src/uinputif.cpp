/*
 * (C) 2014 Kimmo Lindholm <kimmo.lindholm@gmail.com> Kimmoli
 *
 * uinput functions
 *
 *
 *
 *
 */

#include "uinputif.h"

#include "tohkbd.h"
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

static const char *conf_devname = "tohkbd";
const char specialKeys[] = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
                             KEY_KPPLUS, KEY_HOME, KEY_END, KEY_PAGEDOWN, KEY_PAGEUP,
                             0 };

int UinputIf::fd = -1;

UinputIf::UinputIf(QObject *parent) :
    QObject(parent)
{
}


/*
 * open and configure uinput device for tohkbd
 *
 */

int UinputIf::openUinputDevice()
{
    int i;
    struct uinput_user_dev uidev;


    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if(fd < 0)
    {
        writeToLog("uinput: error: open");
        return false;
    }

    if(ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)
    {
        writeToLog("uinput: error: ioctl UI_SET_EVBIT EV_KEY");
        return false;
    }

    if(ioctl(fd, UI_SET_EVBIT, EV_SYN) < 0)
    {
        writeToLog("uinput: error: ioctl UI_SET_EVBIT EV_SYN");
        return false;
    }


    /* Enable most of the keys */
    for (i = KEY_ESC ; i < KEY_NUMLOCK ; i++)
    {
        if(ioctl(fd, UI_SET_KEYBIT, i) < 0)
        {
            writeToLog("uinput: error: ioctl UI_SET_KEYBIT");
            return false;
        }
    }

    i=0;
    while (specialKeys[i] != 0)
    {
        if(ioctl(fd, UI_SET_KEYBIT, specialKeys[i] ) < 0)
        {
            writeToLog("uinput: error: ioctl UI_SET_KEYBIT");
            return false;
        }
        i++;
    }

    //writeToLog("uinput: /dev/uinput opened succesfully.");

    memset(&uidev, 0, sizeof(uidev));
    strncpy(uidev.name, conf_devname, UINPUT_MAX_NAME_SIZE);
    uidev.id.bustype = BUS_VIRTUAL;
    uidev.id.vendor  = 0x4b4c;
    uidev.id.product = 0x4f48;
    uidev.id.version = 1;

    if(write(fd, &uidev, sizeof(uidev)) < 0)
    {
        writeToLog("uinput: error: write uidev");
        return false;
    }

    if(ioctl(fd, UI_DEV_CREATE) < 0)
    {
        writeToLog("uinput: error: ioctl UI_DEV_CREATE");
        return false;
    }

    usleep(100000); /* wait magic 100ms here*/

    return true;
}

/*
 * Send EV_SYN event
 *
 */

int UinputIf::synUinputDevice()
{
    struct input_event     ev;

    usleep(40000);
    memset(&ev, 0, sizeof(struct input_event));
    gettimeofday(&ev.time, NULL);
    ev.type = EV_SYN;
    ev.code = SYN_REPORT;
    ev.value = 0;
    if(write(fd, &ev, sizeof(struct input_event)) < 0)
    {
        writeToLog("uinput: error: EV_SYN write");
        return false;
    }
    return true;

}


/*
 * submits key presses
 * code = KEY_0
 * val = 1 down, 0 up
 *
 */

int UinputIf::sendUinputKeyPress(unsigned int code, int val)
{
    struct input_event     ev;

    usleep(25000); /* sorcery */
    memset(&ev, 0, sizeof(struct input_event));
    gettimeofday(&ev.time, NULL);
    ev.type = EV_KEY;
    ev.code = code;
    ev.value = val;
    if(write(fd, &ev, sizeof(struct input_event)) < 0)
    {
        writeToLog("uinput: error: EV_KEY write");
        return false;
    }

    return true;
}


/*
 * destroys and closes the opened uinput device
 *
 */

int UinputIf::closeUinputDevice()
{
    usleep(100000);

    if(ioctl(fd, UI_DEV_DESTROY) < 0)
    {
        writeToLog("uinput: error: ioctl");
        return false;
    }

    close(fd);
    return true;

}
