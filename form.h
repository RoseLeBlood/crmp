#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "rastream.h"
#include <qtimer.h>
#include "glwidget.h"

#include <qlistwidget.h>

namespace Ui {
class Form;
}

class playList : public QListWidgetItem
{
public:
    playList(QListWidget *other) : QListWidgetItem(other)       { }


    void Create(QString Anzeigen, QString path)
    {
        this->setText(Anzeigen);
        m_path = path;
    }
    QString GetPath() { return m_path; }

private:
   QString     m_path;
};

class Form : public QWidget
{
    Q_OBJECT
    
    raSystem    *m_system;
    raStream    *m_stream;

    GLWidget    *m_gl;
    QTimer      *m_timer;

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    


protected:
    void InitSoundSystem();
private slots:
    void on_Form_destroyed();

    void on_cmdPlay_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_cmdStop_clicked();

    void updatePosition();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Form *ui;
};

#endif // FORM_H
