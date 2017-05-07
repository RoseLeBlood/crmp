#include "qdialog.h"
#include "customdsp.h"
#include "form.h"

/*extern "C"
{
    struct Dsp_Info
    {
        bool (* isCompatible)(long version);
        QWidget* (* getWidget)(QWidget *parent, FMOD::System *system);
        QString (* getName)();
    };
    Dsp_Info* Dsp_Main();
}*/

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
    return "crmp normalize";
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

