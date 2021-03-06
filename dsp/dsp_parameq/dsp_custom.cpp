#include "qdialog.h"
#include "customdsp.h"
#include "form.h"

bool isCompatible(long)
{
    return true;
}

QWidget* getWidget(QWidget *p, FMOD::System *s)
{
    Form *frm= new Form(p);

    frm->setWindowFlags(Qt::Window);
    frm->CreateDspPlugin(s);

    return frm;
}
QString  getName()
{
    return "crmp Param EQ";
}

extern "C"
{
    Dsp_Info* Dsp_Main()
    {
        Dsp_Info *info = new Dsp_Info();
        info->getName = getName;
        info->getWidget = getWidget;
        info->isCompatible = isCompatible;

        return info;
    }

}
