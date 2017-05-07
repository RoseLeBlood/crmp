#include "mainwindow.h"
#include <stdio.h>
#include "openstream.h"
#include <qxmlstream.h>
#include <QFile>
#include <assert.h>

#include "pluginloader.h"
#include "dspaction.h"


QString raRemoveDir(QString Filename)
{
  QStringList mailids = Filename.split("/");

  return mailids.last();
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
    InitSoundSystem();

    setupUi(this);

    m_op.setParent(this, Qt::Window);


    WriteDSPinMenu();
}


void MainWindow::AddFileToPlaylist(QString Path, bool stream)
{
    if(Path.isEmpty()) return;

    playList *item = new playList(listWidget);


    if(stream)
    {

         item->Create(Path, Path);
    }
    else
    {
        if(QFile::exists(Path))
        {

           item->Create(raRemoveDir(Path), Path);
        }
    }
}

void MainWindow::close()
{
  QMainWindow::close();
}

MainWindow::~MainWindow()
{

}

void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      retranslateUi(this);
      break;
    default:
      break;
    }
}
void MainWindow::InitSoundSystem()
{
    m_system = new raSystem();
    crmpSettings::Instance().LoadConfig();
    m_system->Create();
    raStream::Instance().Create(m_system);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
}

void MainWindow::on_cmdPlay_clicked()
{
    if(listWidget->count() <= 0) return;

  playList *item = ( playList *)listWidget->currentItem();
  if(item == NULL)
  {
    listWidget->item(0)->setSelected(true);
    listWidget->setCurrentItem(listWidget->item(0));

    item = ( playList *)listWidget->currentItem();

    if(item == NULL) return;
  }

  m_playedindex = listWidget->currentIndex().row();



  on_cmdStop_clicked();

  if(raStream::Instance().LoadStream(item->GetPath().toLocal8Bit().constData(), true))
  {
      if(!raStream::Instance().PlayStream(raVector3(0.0f, 5.0f, 0.0f), raVector3(0,0,0)))
          return;
      horizontalSlider->setMaximum(raStream::Instance().GetLenght());
      horizontalSlider->setMinimum(0);

       m_timer.start(1);

      QString Title = "";

      QString ArtistTag = raStream::Instance().GetTag("ARTIST", -1);
      QString	AlbumTag = raStream::Instance().GetTag("ALBUM", -1);
      QString	TitleTag = raStream::Instance().GetTag("TITLE", -1);


      if(ArtistTag != "") Title += " " + ArtistTag.simplified();
      if(TitleTag != "") Title += "-" + TitleTag.simplified();
      if(AlbumTag != "") Title += "-" + AlbumTag.simplified();

      if(!Title.isEmpty())
        {
          crmplogger::LogInfo(Title.toStdString(), "on_cmdPlay_clicked");
          this->setWindowTitle(Title.trimmed() + " :: CRMP Audio Player");
        }
      else
        {
          crmplogger::LogInfo( item->text().toStdString(), "on_cmdPlay_clicked");
          this->setWindowTitle(item->text().trimmed() + " :: CRMP Audio Player");
        }

      raStream::Instance().SetVolume((float)this->volumslider->value()/100.0f);
  }
}

void MainWindow::on_cmdStop_clicked()
{
  if(raStream::Instance().IsPlaying())
  {
       m_timer.stop();

      raStream::Instance().StopStream();
      this->setWindowTitle("CRMP Audio Player");
  }

}
void MainWindow::updatePosition()
{
    if(raStream::Instance().IsPlaying())
    {
        if(horizontalSlider->maximum() > 1)
        {
            horizontalSlider->setValue(raStream::Instance().GetPosition());
        }
        m_system->Update();
    }
    else
    {
      m_timer.stop();
      this->setWindowTitle("CRMP Audio Player");


      int next = m_playedindex + 1;

      if(next >= listWidget->count())
        return;

      listWidget->item(next)->setSelected(true);
      listWidget->setCurrentItem(listWidget->item(next));

      on_cmdPlay_clicked();
    }

}



void MainWindow::on_actionPlay_triggered()
{
    on_cmdPlay_clicked();
}

void MainWindow::on_actionStop_triggered()
{
    on_cmdStop_clicked();
}

void MainWindow::on_actionPause_triggered()
{
    raStream::Instance().PauseStream();
}

void MainWindow::on_actionClear_triggered()
{
    this->listWidget->clear();
}

void MainWindow::on_actionFile_Open_2_triggered()
{
  QString selfilter = tr("Audio Format (*.mp2 *.mp3 *.ogg *.flac *.wav *.s3m)");
  QString fileName = QFileDialog::getOpenFileName(
          this,
          "Open Audio File",
          "",
        tr("Audio Format (*.mp2 *.mp3 *.ogg *.flac *.wav *.s3m *.aiff *.asf *.dls *.it)" ),
          &selfilter
  );

  AddFileToPlaylist(fileName);
}

void MainWindow::on_pushButton_3_clicked()
{
  if(!raStream::Instance().IsPlaying()) return;

  int next = m_playedindex - 1;

  if(next < 0)  return;

  listWidget->item(next)->setSelected(true);
  listWidget->setCurrentItem(listWidget->item(next));

  on_cmdPlay_clicked();
}

void MainWindow::on_cmdVor_clicked()
{
  if(!raStream::Instance().IsPlaying()) return;

  int next = m_playedindex + 1;

  if(next >= listWidget->count())
    return;

  listWidget->item(next)->setSelected(true);
  listWidget->setCurrentItem(listWidget->item(next));

  on_cmdPlay_clicked();
}


void MainWindow::on_actionOpen_Dir_triggered()
{
  QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
  QString directory = QFileDialog::getExistingDirectory(this,
                             tr("CRMP Open Dir"),
                             "",
                             options);

 listWidget->clear();

  QDirIterator it(directory, QDirIterator::Subdirectories);
  while (it.hasNext())
  {
      QString item = it.next();

     if(isPlayerfile(item))
     {
         AddFileToPlaylist(item);
     }
  }
  listWidget->sortItems();
}
std::string MainWindow::raGetFilenameExtension(std::string Filename)
{
    int iLastDot;
    int iChar;

    // Letzten Punkt (".") im Dateinamen suchen
    iLastDot = -1;
    iChar = 0;
    while(Filename[iChar] != 0)
    {
            if(Filename[iChar] == '.') iLastDot = iChar;
            iChar++;
    }
    // String ab dem letzten Punkt plus 1 zur�ckliefern
    return std::string(Filename.c_str() + iLastDot + 1);
}



bool MainWindow::isPlayerfile(QString input)
{
  //*.mp2 *.mp3 *.ogg *.flac *.wav  *.s3m *.aiff *.asf *.dls *.it

  QString temp = QString::fromStdString(raGetFilenameExtension(input.toStdString()));

  return (temp == "mp3" ||
          temp == "mp2" ||
          temp == "wav" ||
          temp == "ogg" ||
          temp == "flac" ||
          temp == "wma" ||
          temp == "s3m" ||
          temp == "aiff" ||
          temp == "asf" ||
          temp == "dls" ||
          temp == "it");

}





void MainWindow::on_actionExit_2_triggered()
{
    this->close();
}

void MainWindow::on_actionStream_triggered()
{
    m_op.setVisible(true);
}

void MainWindow::on_actionInfo_triggered()
{
    m_info.show();
}

void MainWindow::on_actionOpen_triggered()
{

    QString selfilter = tr("xml Playlist (*.xml)");
    QString filename = QFileDialog::getOpenFileName(
            this,
            "Open Playlist File",
            "",
            selfilter,
            &selfilter
    );

    if(m_playlist.Open(filename))
      {
        m_playlist.WriteInListView(this->listWidget);
        m_playlist.Close();
      }

}




void MainWindow::on_volumslider_valueChanged(int value)
{
    raStream::Instance().SetVolume((float)value/100.0f);
}


void MainWindow::OnTriggerd()
{
    dspAction *s = (dspAction*) sender();

    QWidget *qw = s->data->getWidget(this, raStream::Instance().GetSystem());

    qw->show();
}

void MainWindow::WriteDSPinMenu()
{


    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    dir.setPath(crmpSettings::Instance().GetDSPPath());



    QStringList filters;
    filters << "*.dsp";
    dir.setNameFilters(filters);


    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);

        Dsp_Info *info = PluginLoader::scanforPlugins(fileInfo.filePath());

        if(info)
        {
            dspAction *action = new dspAction(info->getName(), this);

            action->data = info;
            menuPlugin->addAction(action);
            connect(action, SIGNAL(triggered()),this, SLOT(OnTriggerd()));
        }

    }
}



void MainWindow::on_listWidget_doubleClicked(const QModelIndex &)
{
    on_cmdPlay_clicked();
}


void MainWindow::on_actionSave_As_triggered()
{
  QString selfilter = tr("xml Playlist (*.xml)");
  QString filename = QFileDialog::getSaveFileName(
          this,
          "Save Playlist File",
          "",
          selfilter,
          &selfilter
  );

  if(m_playlist.Open(filename))
    {
      m_playlist.SaveInFileFromListView(this->listWidget);
      m_playlist.Close();
    }
}

void MainWindow::on_actionPlaylist_triggered()
{
    this->listWidget->setVisible(!listWidget->isVisible());
}
