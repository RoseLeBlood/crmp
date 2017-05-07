#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T15:49:06
#
#-------------------------------------------------

TARGET = dsp_normalize
TEMPLATE = lib

DEFINES += DSP_NORMALIZE_LIBRARY

SOURCES += dsp_normalize.cpp \
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
