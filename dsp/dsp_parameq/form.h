#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <rastream.h>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    
    void CreateDspPlugin(FMOD::System* Instance);

    virtual void closeEvent ( QCloseEvent * event );
private slots:
    void on_ParamEQA_toggled(bool arg1);

    void on_center2_valueChanged(int value);

    void on_bandwidth2_valueChanged(int value);

    void on_gain2_valueChanged(int value);

    void on_cmdReset_clicked();

    void on_Form_destroyed();

private:
    Ui::Form *ui;

    FMOD::DSP       *m_parameq;
    FMOD::System    *m_system;
};

#endif // FORM_H
