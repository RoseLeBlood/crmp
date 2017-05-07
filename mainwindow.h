#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "version.h"
#include "ui_mainwindow.h"
#include "rastream.h"
#include <qtimer.h>
#include "crmplogger.h"
#include "xplreader.h"
#include "openstream.h"
#include "info.h"
#include <QFileDialog>
#include <QDirIterator>
#include <pluginloader.h>


class playList : public QListWidgetItem
{
public:
    playList(QListWidget *other = 0) : QListWidgetItem(other)       { }


    void Create(QString Anzeigen, QString path)
    {
        this->setText(Anzeigen);
        m_path = path;
    }
    QString GetPath() { return m_path; }

private:
   QString     m_path;
};

class MainWindow : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT
  
  raSystem    *m_system;

  QSize         m_oldsize;
  QTimer        m_timer;
  int           m_playedindex;
  OpenStream    m_op;
  info          m_info;
  PluginLoader  m_plugin;
  crmpPlaylist  m_playlist;
public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

  void AddFileToPlaylist(QString Path, bool stream = false) ;
protected:
    void InitSoundSystem();

protected:
  void changeEvent(QEvent *e);
  void close();


  void WriteDSPinMenu();
private:
  bool isPlayerfile(QString input);
  std::string raGetFilenameExtension(std::string Filename);
private slots:
  void on_cmdPlay_clicked();
  void on_cmdStop_clicked();
  void updatePosition();

  void on_actionPlay_triggered();
  void on_actionStop_triggered();
  void on_actionPause_triggered();
  void on_actionClear_triggered();
  void on_actionFile_Open_2_triggered();
  void on_pushButton_3_clicked();
  void on_cmdVor_clicked();
  void on_actionOpen_Dir_triggered();

  void on_actionExit_2_triggered();
  void on_actionStream_triggered();
  void on_actionInfo_triggered();
  void on_actionOpen_triggered();

  void on_volumslider_valueChanged(int value);

   void OnTriggerd();

   void on_listWidget_doubleClicked(const QModelIndex &index);
   void on_actionSave_As_triggered();
   void on_actionPlaylist_triggered();
};

#endif // MAINWINDOW_H
