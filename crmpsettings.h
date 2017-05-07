#ifndef CRMPSETTINGS_H
#define CRMPSETTINGS_H

#include "QtGui"
#include <fmodex/fmod.hpp>

#define CRMP_DSP_PATH "/usr/share/crmp"

namespace ResampleMode
{
	enum ResampleMode_t
	{
		NoResample = 0,
		Linear = 1,
		Cubic = 2,
		Spline = 3,
	};
}

class crmpSettings
{
private:
    QString             m_dpspath;
    int                 m_samplerate;
    int                 m_bit;
    QSettings::Format   m_format;
    int    		m_mode;
    int			m_soundKarte;

    ResampleMode::ResampleMode_t m_resampleMode;
private:
    crmpSettings();

    static crmpSettings *m_instance;
public:
    void LoadConfig();

    QString GetDSPPath()
    {
        return m_dpspath;
    }

    int     GetSamplerate()
    {
        return m_samplerate;
    }
    int     GetBits()
    {
        return m_bit;
    }
    int GetSpeakerMode() 
    { 
	return m_mode; 
    }
    int GetSoundkarte()
    {
        return m_soundKarte;
    }
    ResampleMode::ResampleMode_t GetResampleMode()
    {
	return m_resampleMode;
    }
    
    static crmpSettings& Instance()
    {
        if(m_instance == NULL)
            m_instance = new crmpSettings();

        return *m_instance;
    }

};

#endif // CRMPSETTINGS_H
