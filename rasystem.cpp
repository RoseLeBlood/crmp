#include "rasystem.h"
#include <iostream>
#include <stdio.h>
#include <crmplogger.h>

raSystem::raSystem()
{
}
raSystem::~raSystem()
{
    if(m_system) { m_system->release(); m_system->release(); delete m_system; }

}

bool raSystem::ERRCHECK(FMOD_RESULT result, const char *Func)
{
    if (result != FMOD_OK)
    {
        crmplogger::LogError(FMOD_ErrorString(result), Func);
        return false;
    }
    return true;

}
void raSystem::Update()
{
    m_system->update();
}

bool raSystem::Create()
{
    unsigned int version = 0;
    FMOD_SPEAKERMODE speakerMode;
    FMOD_CAPS caps;
    FMOD_DSP_RESAMPLER resampler;
    int numdrivers = 0;
    int confSoundkarte = crmpSettings::Instance().GetSoundkarte();

        FMOD_RESULT result = FMOD::System_Create(&m_system);
        if(!ERRCHECK(result)) return false;

        result = m_system->getVersion(&version);
        if(!ERRCHECK(result)) return false;

        if (version < FMOD_VERSION)
        {
            std::cout << "INCORRECT FMOD VERSION!!" << std::endl;
            return false;
        }
	result = m_system->getNumDrivers(&numdrivers);
	ERRCHECK(result);

	if(numdrivers < confSoundkarte)
	{
		std::cout << "Using Default device! Device no: " << confSoundkarte << " not found" << std::endl;
		for (int count=0; count < numdrivers; count++)
		{
			char name[256];

			result = m_system->getDriverInfo(count, name, 256, 0);
			ERRCHECK(result);

			printf("%d : %s\n", count, name) ;
		}
		confSoundkarte = 0;
		std::cout << std::endl;
	}
	

        // Set Soundkarte
        result = m_system->setDriver(confSoundkarte);
        ERRCHECK(result);

	result = m_system->getDriverCaps(0, &caps, 0, &speakerMode);
        ERRCHECK(result);

	
	if(crmpSettings::Instance().GetSpeakerMode() == 0)
	{
        	result = m_system->setSpeakerMode(speakerMode);
        	ERRCHECK(result);
	}
	else
	{
		result = m_system->setSpeakerMode((FMOD_SPEAKERMODE)(crmpSettings::Instance().GetSpeakerMode()));
        	ERRCHECK(result);
	}


        // Increase buffer size if user has Acceleration slider set to off
        if (caps & FMOD_CAPS_HARDWARE_EMULATED)
        {
            result = m_system->setDSPBufferSize(1024, 10);
            ERRCHECK(result);
        }

        FMOD_SOUND_FORMAT format;

        switch(crmpSettings::Instance().GetBits())
        {
        case 8: format = FMOD_SOUND_FORMAT_PCM8; break;
        case 16: format = FMOD_SOUND_FORMAT_PCM16; break;
        case 24: format = FMOD_SOUND_FORMAT_PCM24; break;
        case 32: format = FMOD_SOUND_FORMAT_PCMFLOAT; break;
        default: format = FMOD_SOUND_FORMAT_PCM16; break;
        }

	switch(crmpSettings::Instance().GetResampleMode())
	{
	case ResampleMode::NoResample: resampler = FMOD_DSP_RESAMPLER_NOINTERP ; break;
	case ResampleMode::Linear: resampler = FMOD_DSP_RESAMPLER_LINEAR ; break;
	case ResampleMode::Cubic: resampler = FMOD_DSP_RESAMPLER_CUBIC; break;
	
	case ResampleMode::Spline: 
	default: resampler = FMOD_DSP_RESAMPLER_SPLINE; break;
	};
	
        m_system->setSoftwareFormat(crmpSettings::Instance().GetSamplerate(), format, 0,0, resampler); //FMOD_DSP_RESAMPLER_LINEAR);
        // FMOD Initialisieren
        result = m_system->init(32, FMOD_INIT_NORMAL , 0);
        if(!ERRCHECK(result)) return false;


        //m_system->setAdvancedSettings();

        m_system->set3DSettings(1.0, 1.0f, 1.0f);
        this->Update();

        crmplogger::LogOk("Sound Engine Initialisiert", "Create");


        plotinfo();

    return true;

}


void raSystem::plotinfo()
{
   FMOD_SPEAKERMODE format;
   const char* sformat = "";

   int samplerate = 0;
   int bits = 0;

   m_system->getSoftwareFormat(&samplerate, 0, 0,0,0, &bits);
   m_system->getSpeakerMode(&format);

   switch(format)
   {
     case FMOD_SPEAKERMODE_MONO: sformat = "Mono"; break;
     case FMOD_SPEAKERMODE_STEREO: sformat = "Stereo"; break;
     case FMOD_SPEAKERMODE_QUAD: sformat = "Quad"; break;
     case  FMOD_SPEAKERMODE_5POINT1: sformat = "5.1"; break;
     case FMOD_SPEAKERMODE_SURROUND: sformat ="Surround"; break;
     case FMOD_SPEAKERMODE_7POINT1: sformat = "7.1"; break;
     case FMOD_SPEAKERMODE_SRS5_1_MATRIX: sformat = "SRS 5.1"; break;
     case FMOD_SPEAKERMODE_MYEARS: sformat = "MyEars"; break;
     default: sformat = "other"; break;
   }
   char buf[64];
   sprintf(buf, "PCM Format Bits: %d Samplerate: %d Speaker Mode: %s", bits, samplerate, sformat);
   crmplogger::LogInfo(buf, "plotinfo");
}
