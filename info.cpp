#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
    this->setParent(parent, Qt::Window);
}

info::~info()
{
    delete ui;
}

void info::on_buttonBox_clicked(QAbstractButton *)
{
    this->close();
}
