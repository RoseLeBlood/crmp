#ifndef DSPACTION_H
#define DSPACTION_H

#include <QAction>
#include "customdsp.h"

class dspAction : public QAction
{
public:
    explicit dspAction(const QString &text, QObject *parent);

    Dsp_Info *data;
};

#endif // DSPACTION_H
