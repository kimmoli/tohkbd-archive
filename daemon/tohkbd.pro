TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt
QT += dbus
QT -= gui

INCLUDEPATH += ./inc

SOURCES += \
    src/tohkbd.cpp \
	src/toh.cpp \
    src/tca8424.cpp \
    src/worker.cpp \
    src/tohkeyboard.cpp \
    src/uinputif.cpp

HEADERS += \
    inc/toh.h \
    inc/tca8424.h \
    inc/worker.h \
    inc/tohkeyboard.h \
    inc/uinputif.h

OTHER_FILES += \
    rpm/tohkbd.spec

