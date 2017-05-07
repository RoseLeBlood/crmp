#ifndef OPENSTREAM_H
#define OPENSTREAM_H

#include <QDialog>

namespace Ui {
class OpenStream;
}

class OpenStream : public QDialog
{
    Q_OBJECT
    
public:
    explicit OpenStream(QWidget *parent = 0);
    ~OpenStream();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::OpenStream *ui;
};

#endif // OPENSTREAM_H
