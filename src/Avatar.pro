#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T15:11:13
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Avatar
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    avatar.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib/x86_64-linux-gnu/release/ -lSDL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib/x86_64-linux-gnu/debug/ -lSDL
else:unix: LIBS += -L$$PWD/../../../../../../usr/lib/x86_64-linux-gnu/ -lSDL

INCLUDEPATH += $$PWD/../../../../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../../../usr/lib/x86_64-linux-gnu

HEADERS += \
    avatar.h
