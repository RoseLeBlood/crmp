#ifndef CUSTOMDSP_H
#define CUSTOMDSP_H


#include "fmodex/fmod.hpp"
#include <QtGui>



extern "C"
{
    struct Dsp_Info
    {
        bool (* isCompatible)(long version);
        QWidget* (* getWidget)(QWidget *parent, FMOD::System *system);
        QString (* getName)();
    };
    Dsp_Info* Dsp_Main();
}

#endif // CUSTOMDSP_H
