#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T14:39:56
#
#-------------------------------------------------

TARGET = dsp_parameq
TEMPLATE = lib

DEFINES += DSP_CUSTOM_LIBRARY

SOURCES += dsp_custom.cpp \
    form.cpp

HEADERS += \
    form.h

INCLUDEPATH += ../../

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    form.ui

QT += widgets
