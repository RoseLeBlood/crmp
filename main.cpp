#include <QApplication>
#include "mainwindow.h"
#include "iostream"
#include "stdio.h"
#include "crmpsettings.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.thread()->setPriority(QThread::HighPriority);

    MainWindow w;



    QStringList list = qApp->arguments();
    list[0] = "";


    for (QStringList::iterator it = list.begin();
             it != list.end(); ++it)
    {
        QString current = *it;
        w.AddFileToPlaylist(current);
    }
    w.show();



    return (a.exec());
}
