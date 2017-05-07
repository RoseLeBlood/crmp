#include "crmpsettings.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QStringList>
#include <QDebug>
#include <crmplogger.h>
#include <xmlformat.h>

#define CONFIG_VERSION "1.3"

crmpSettings *crmpSettings::m_instance = NULL;



crmpSettings::crmpSettings()
{
    m_format = XmlFormat::getFormat();

}
void crmpSettings::LoadConfig()
{
    QSettings *settings = new QSettings("/etc/crmp.xml", m_format );

    QString Version = settings->value("Version", "0.0").toString();
    if(Version != CONFIG_VERSION)
 	throw "Wrong Config Version";

    m_dpspath = settings->value("DSP", CRMP_DSP_PATH).toString();
    m_samplerate = settings->value("Samplerate", 44100).toInt();
    m_bit = settings->value("Bit", 16).toInt();

    int channels = settings->value("Channel", 2).toInt();
    m_soundKarte = settings->value("Soundkarte", 0).toInt();

    m_resampleMode = (ResampleMode::ResampleMode_t)(settings->value("ResampleMode", 0).toInt());

    QString output = "Config: ";
    output.append("Plugin-Path: ");
    output.append(m_dpspath);
    output.append(" Samplrate: ");
    output.append(QString::number(m_samplerate));
    output.append(" Bits: ");
    output.append(QString::number(m_bit));
    output.append(" Speakermode: ");
    

    switch(channels)
    {
	case 1:
		m_mode = FMOD_SPEAKERMODE_MONO; output.append("Mono");
		break;
	case 2:
	case 3:
		m_mode = FMOD_SPEAKERMODE_STEREO; output.append("Stereo");
		break; 
	case 4: // Quad Stereo
		m_mode = FMOD_SPEAKERMODE_QUAD; output.append("Quad");
		break;
	case 5:
		m_mode = FMOD_SPEAKERMODE_SURROUND; output.append("Surround");
		break;
	case 6: // 5.1
		m_mode = FMOD_SPEAKERMODE_5POINT1; output.append("5.1");
		break;
	case 7:
	case 8: // 7.1
		m_mode = FMOD_SPEAKERMODE_7POINT1; output.append("7.1");
		break;
	case 9: 
		m_mode = FMOD_SPEAKERMODE_SRS5_1_MATRIX; output.append("SRS 5.1");
		break;
	default:
		m_mode = -1; output.append("System");
		break; 

    };
    if(settings) { delete settings; settings = 0; }

    

    crmplogger::LogOk(output.toStdString().data(), "LoadConfig");
}

