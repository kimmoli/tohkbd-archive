dbus configuration file and systemd service file

  .conf goes to /etc/dbus-1/system.d/

  .service goes to /etc/systemd/system/

NOTE1: The .service file expects that the tohkbd binary goes to /home/nemo/test -folder

You might need to chmod it to executable.

Some files you need to copy in place as root


NOTE2: These are developer versions. 

dbus configuration will be removed in final version.
