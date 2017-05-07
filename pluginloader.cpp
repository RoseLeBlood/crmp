#include "pluginloader.h"
#include <QFile>
#include <QLibrary>
#include <dlfcn.h>
#include <version.h>
#include <qdir.h>
#include <iostream>
#include "rastream.h"
#include "customdsp.h"

//void DSP_PluginMain(raStream* instance, QWidget* Parent)
typedef Dsp_Info* (*DSP_PluginMain_t)();

/*
struct Dsp_Info
{
    bool (* isCompatible)(long version);
    DSP_Widget (* getWidget)(QWidget *parent);
    QString (* getName)();
};
extern struct Dsp_Info Dsp_Main();*/



Dsp_Info* PluginLoader::scanforPlugins(QString plugin)
{
    if(!QFile::exists(plugin)) return 0;

    try
    {
        QLibrary qlib(plugin);

        if(qlib.load())
        {
          DSP_PluginMain_t DSP_PluginMain = (DSP_PluginMain_t) qlib.resolve("Dsp_Main");

          if(DSP_PluginMain)
            return DSP_PluginMain();

        }
    }
    catch(... )
    {


    }
    return NULL;
}

