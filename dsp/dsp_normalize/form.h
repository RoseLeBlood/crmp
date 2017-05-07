#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "rasystem.h"
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

    void on_threshhold_valueChanged(int value);

    void on_Maxamp_valueChanged(int value);

    void on_fadetime_valueChanged(int value);

    void on_cmdNormalizeReset_clicked();

    void on_Normalize_toggled(bool arg1);

private:
    Ui::Form *ui;
    FMOD::DSP       *m_normalize;
    FMOD::System    *m_system;
};

#endif // FORM_H
