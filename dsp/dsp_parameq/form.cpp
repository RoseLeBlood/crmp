#include "form.h"
#include "ui_form.h"

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
    m_system->createDSPByType(FMOD_DSP_TYPE_PARAMEQ, &this->m_parameq);

}
void Form::closeEvent ( QCloseEvent * event )
{
    m_parameq->remove();
    QWidget::closeEvent(event);
}

void Form::on_ParamEQA_toggled(bool arg1)
{
    if(!arg1)
    {
        m_parameq->remove();
    }
    else
    {
        m_system->addDSP(m_parameq,0);
        m_parameq->setParameter(FMOD_DSP_PARAMEQ_BANDWIDTH, ui->bandwidth2->value()/10.0f);
        m_parameq->setParameter(FMOD_DSP_PARAMEQ_GAIN, ui->gain2->value()/100.0f);
        m_parameq->setParameter(FMOD_DSP_PARAMEQ_CENTER, ui->center2->value());
    }
}

void Form::on_bandwidth2_valueChanged(int value)
{
    m_parameq->setParameter(FMOD_DSP_PARAMEQ_BANDWIDTH, (float)(value/10.0f));
    ui->lblband2->setText(QString::number(value));
}
void Form::on_gain2_valueChanged(int value)
{
    m_parameq->setParameter(FMOD_DSP_PARAMEQ_GAIN, (float)(value/100.0f));
    ui->lblgain2->setText(QString::number(value));
}
void Form::on_center2_valueChanged(int value)
{
    m_parameq->setParameter(FMOD_DSP_PARAMEQ_CENTER, value);
    ui->lblcenter2->setText(QString::number(value));
}

void Form::on_cmdReset_clicked()
{
    ui->center2->setValue(8000);
    ui->bandwidth2->setValue(10);
    ui->gain2->setValue(100);
}

void Form::on_Form_destroyed()
{
    m_parameq->remove();
}
