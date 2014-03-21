tohkbd
======

Jolla TOH keyboard

Folder | Waht there?
-------|-------------------------------------
bin    | Executable <br> Copy file __tohkbd__ to __/home/nemo/test__ folder and give it execute rights (`chmod 755 tohkbd`)<br> Folder can be changed by editing __tohkbd.service__ file
config | System configuration files (systemd, dbus, udev...) <br> You need root rights to copy these files in place (`devel-su`). <br> __tohkbd.conf__ goes to goes to __/etc/dbus-1/system.d/__ <br> __tohkbd.service__ goes to __/etc/systemd/system/__
vkb    | Virtual keyboard to assist external keyboard with clipboard etc. <br> these files goes to __/usr/share/maliit/plugins/com/jolla/layouts/__<br> Note that you might need to restart maliit (not root) `systemctl --user restart maliit-server.service` and possible to check TOHKBD in Settings->Input...
pcb    | Eagle files (Schematic, Board)
stl    | 3D Models for printing
daemon | Sources for daemon. QtCreator project, just build (no deployment)

To get the service started (root) `systemctl start tohkbd.service`

To follow daemon log output `journalctl _SYSTEMD_UNIT=tohkbd.service -f`


Note that all key presses are logged so take that into account when entering passwords, etc if you also plan to post your device's logfiles to the internet.


More stuff here https://www.dropbox.com/sh/fxocsudk5gd8chs/q587RKRDhk/QWERTY%20OH



