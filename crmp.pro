#-------------------------------------------------
#
# Project created by QtCreator 2012-08-17T19:36:53
#
#-------------------------------------------------

QT       += core gui
#CONFIG   += x11  link_pkgconfig uic

VERSION = 0.99.2645

QMAKE_CXXFLAGS += -std=c++0x
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = crmp
TEMPLATE = app

PRECOMPILED_HEADER = pch.h

SOURCES += main.cpp\
        mainwindow.cpp \
    rastream.cpp \
    rasystem.cpp \
    openstream.cpp \
    info.cpp \
    xplreader.cpp \
    pluginloader.cpp \
    dspaction.cpp \
    crmpsettings.cpp \
    xmlformat.cpp

HEADERS  += mainwindow.h \
    rasystem.h \
    crmplogger.h \
    rastream.h \
    customdsp.h \
    openstream.h \
    info.h \
    xplreader.h \
    version.h \
    pluginloader.h \
    dspaction.h \
    pch.h \
    crmpsettings.h \
    xmlformat.h

FORMS    += mainwindow.ui \
    openstream.ui \
    info.ui


LIBS += -lfmodex



contains(QMAKE_HOST.arch, x86_64):{
unix:!symbian|win32: LIBS += -lfmodex64
unix:!symbian|win32: LIBS -= -lfmodex
}


unix:!symbian: LIBS += -ldl
