#include "openstream.h"
#include "ui_openstream.h"
#include "mainwindow.h"

OpenStream::OpenStream(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenStream)
{
    ui->setupUi(this);
}

OpenStream::~OpenStream()
{
    delete ui;
}
void OpenStream::on_pushButton_clicked()
{
    if(!ui->txtstream->toPlainText().isEmpty())
    {
        MainWindow* m = (MainWindow*)this->parent();
        m->AddFileToPlaylist(ui->txtstream->toPlainText(), true);
        ui->txtstream->setPlainText("");
        m = NULL;
    }

    this->close();
}

void OpenStream::on_pushButton_2_clicked()
{
    this->close();
}
