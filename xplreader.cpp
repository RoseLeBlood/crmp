#include "xplreader.h"
#include "xmlformat.h"
#include "mainwindow.h"
#include "QString"
crmpPlaylist::crmpPlaylist()
{

}

bool crmpPlaylist::Open(QString FileName)
{
  m_playlist = new QSettings(FileName, XmlFormat::getFormat());
  return (m_playlist != NULL);

}

void crmpPlaylist::WriteInListView(QListWidget* lsview)
{
  if(!m_playlist || !lsview) return;
  lsview->clear();
  int m_entrys = m_playlist->value("Items", 0).toInt();

  for(int i=0; i < m_entrys; i++)
  {
      m_playlist->beginGroup(QString("Track") + QString::number(i));
      QString anzeig = m_playlist->value(QString("Info"), "-NOT_A_TAG").toString();
      QString path = m_playlist->value(QString("FilePath"), "-NOT_A_FILE").toString();
      m_playlist->endGroup();

      if(path != "-NOT_A_FILE")
      {
          if(anzeig != "-NOT_A_TAG")
            {
              playList *item = new playList(lsview);
              item->Create(anzeig, path);
            }
          else
            {
              playList *item = new playList(lsview);
              item->Create(path, path);
            }
      }
  }
  lsview->sortItems();
}

void crmpPlaylist::SaveInFileFromListView(QListWidget *lsview)
{
  if(!m_playlist) return;

  m_playlist->setValue("Items", lsview->count());

  for(int i=0; i < lsview->count(); i++)
    {
      m_playlist->beginGroup(QString("Track") + QString::number(i));
      m_playlist->setValue(QString("Info"), ((playList*)lsview->item(i))->text());
      m_playlist->setValue(QString("FilePath"), ((playList*)lsview->item(i))->GetPath());
      m_playlist->endGroup();
    }
}

bool crmpPlaylist::Close()
{
  if(m_playlist)
    {
      delete m_playlist;
      return true;
    }
  return false;
}
