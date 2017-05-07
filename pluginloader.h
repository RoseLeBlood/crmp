#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QMenu>
#include <QString>
#include "customdsp.h"

class PluginLoader
{

public:
    static Dsp_Info *scanforPlugins(QString plugin);
};

#endif // PLUGINLOADER_H
