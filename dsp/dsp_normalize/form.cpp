#include "form.h"
#include "ui_form.h"
#include "rasystem.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}
void Form::CreateDspPlugin(FMOD::System *system)
{
    m_system = system;
    m_system->createDSPByType(FMOD_DSP_TYPE_NORMALIZE, &this->m_normalize);

}
void Form::closeEvent ( QCloseEvent * event )
{
    m_normalize->remove();
    QWidget::closeEvent(event);
}

void Form::on_fadetime_valueChanged(int value)
{
    m_normalize->setParameter(FMOD_DSP_NORMALIZE_FADETIME, value);
    ui->lblfadeTime->setText(QString::number(value));
}

void Form::on_threshhold_valueChanged(int value)
{
    m_normalize->setParameter(FMOD_DSP_NORMALIZE_THRESHHOLD, (float)(value/100.0f));
    ui->lblthreshhold->setText(QString::number(value));
}

void Form::on_Maxamp_valueChanged(int value)
{
    m_normalize->setParameter(FMOD_DSP_NORMALIZE_MAXAMP, value);
    ui->lblmaxamp->setText(QString::number(value));
}

void Form::on_Normalize_toggled(bool arg1)
{
    if(!arg1)
    {
        m_normalize->remove();
    }
    else
    {
        m_system->addDSP(m_normalize, 0);
        m_normalize->setParameter(FMOD_DSP_NORMALIZE_FADETIME, ui->fadetime->value());
        m_normalize->setParameter(FMOD_DSP_NORMALIZE_THRESHHOLD, ui->threshhold->value()/100.0f);
        m_normalize->setParameter(FMOD_DSP_NORMALIZE_MAXAMP, ui->Maxamp->value());
    }
}

void Form::on_cmdNormalizeReset_clicked()
{
    ui->fadetime->setValue(5000);
    ui->threshhold->setValue(10);
    ui->Maxamp->setValue(20);
}




