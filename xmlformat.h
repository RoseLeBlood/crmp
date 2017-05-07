#ifndef XMLFORMAT_H
#define XMLFORMAT_H

#include <QSettings>
#include <QString>

class XmlFormat
{
public:
    XmlFormat();


     static QSettings::Format getFormat() { return QSettings::registerFormat("xml", readXmlFile, writeXmlFile); }
private:
     static bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map);
     static bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map);
};

#endif // XMLFORMAT_H
