#ifndef INFO_H
#define INFO_H

#include "version.h"
#include <QWidget>
#include <qabstractbutton.h>

namespace Ui {
class info;
}

class info : public QWidget
{
    Q_OBJECT
    
public:
    explicit info(QWidget *parent = 0);
    ~info();
    
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::info *ui;
};

#endif // INFO_H
