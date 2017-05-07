#ifndef XPLREADER_H
#define XPLREADER_H


#include <QSettings>
#include <QListWidget>

class crmpPlaylist
{
public:
  crmpPlaylist();

  bool Open(QString FileName);

  void WriteInListView(QListWidget *lsview);
  void SaveInFileFromListView(QListWidget* lsview);

  bool Close();
private:
    QSettings     *m_playlist;
};

#endif // XPLREADER_H
