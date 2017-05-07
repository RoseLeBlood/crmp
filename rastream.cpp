#include "rastream.h"
#include <iostream>

#define SAFE_DELETE(x) if(x) { delete x; x = NULL; }

raStream* raStream::m_instance = 0;

bool raStream::Create(raSystem* AudioSystem)
{
    m_sound = NULL;
    m_channel = NULL;
    m_system = NULL;


    m_system = AudioSystem;
    return true;
}

void raStream::Destroy()
{
    FMOD_RESULT result;

    StopStream();
    result = m_sound->release();
    if(!ERRCHECK(result, "m_sound::Release")) return;

    SAFE_DELETE(m_channel);
}
bool raStream::LoadStream(const char *FileName, bool b3D)
{
    FMOD_RESULT result;
    FMOD::System* sys = m_system->GetSystem();

    if(sys)
    {
        result = sys->setStreamBufferSize(64 * 1024, FMOD_TIMEUNIT_RAWBYTES);
	if(!ERRCHECK(result, "sys::setStreamBufferSize")) return false;

        result = sys->createStream(FileName,  (b3D ) ? FMOD_3D : FMOD_2D | FMOD_HARDWARE | FMOD_NONBLOCKING |
                                 FMOD_MPEGSEARCH , 0, &m_sound);
        if(!ERRCHECK(result, "sys::createStream")) return false;



        return true;

    }
    return false;
}
bool raStream::PlayStream(raVector3 Position, raVector3 Velocity, float minDistance,
        float maxDistance)
{
    if(!m_system) { return false; }

    if(m_channel)
    {
        m_channel->stop();
    }
    FMOD_RESULT result = m_system->GetSystem()->playSound(FMOD_CHANNEL_REUSE, m_sound, true, &m_channel);
    if(!ERRCHECK(result,"playSound" )) return false;

    FMOD_VECTOR pos, velo;
    pos.x = Position.x;
    pos.y = Position.y;
    pos.z = Position.z;

    velo.x = Velocity.x;
    velo.y = Velocity.y;
    velo.z = Velocity.z;


    result = m_channel->set3DAttributes(&pos, &velo );
    if(!ERRCHECK(result,"set3DAttributes" )) return false;


    Set3DMinMaxDistance(minDistance, maxDistance);

    result = m_channel->setPaused(false);
    if(!ERRCHECK(result, "setPaused")) return false;

    return true;
}
bool raStream::PauseStream()
{
    static bool m_paused;

    if(m_channel )
    {
        FMOD_RESULT result = m_channel->getPaused(&m_paused);
        if(!ERRCHECK(result, "getPaused")) return false;

        result =m_channel->setPaused(!m_paused);
        if(!ERRCHECK(result, "setPaused")) return false;
    }
    return true;
}
bool raStream::StopStream()
{
    if(m_channel)
    {
        m_channel->stop();
        CloseStream();
    }
    return true;
}
bool raStream::CloseStream()
{
    FMOD_RESULT result = FMOD_OK;
    if(m_sound)
    {
        result = m_sound->release();
        m_channel = NULL;
    }
    return ERRCHECK(result, "raStream::CloseStream");
}
void raStream::Set3DMinMaxDistance(float min, float max)
{
    m_sound->set3DMinMaxDistance(min, max);
}
bool raStream::SetVelocity(raVector3& vec)
{
    if (m_channel)
    {
        FMOD_VECTOR pos;
        FMOD_RESULT result = m_channel->get3DAttributes( (FMOD_VECTOR*)&pos, 0);
        if(!ERRCHECK(result, "SetVelocity::get3DAttributes")) return false;

        pos.x = vec.x;
        pos.y = vec.y;
        pos.z = vec.z;

        result = m_channel->set3DAttributes( (FMOD_VECTOR*)&pos, (FMOD_VECTOR*)&pos );
        if(!ERRCHECK(result, "SetVelocity::set3DAttributes")) return false;

        return true;
    }
    return false;
}
bool raStream::Set3DPosition(raVector3& vec)
{
    if (m_channel)
    {
        FMOD_VECTOR vel;

        FMOD_RESULT result = m_channel->get3DAttributes( 0, (FMOD_VECTOR*)&vel);
        if(!ERRCHECK(result, "Set3DPosition::get3DAttributes")) return false;

        vel.x = vec.x;
        vel.y = vec.y;
        vel.z = vec.z;

        result = m_channel->set3DAttributes( (FMOD_VECTOR*)&vec, (FMOD_VECTOR*)&vel );
        if(!ERRCHECK(result, "Set3DPosition::set3DAttributes")) return false;

        return true;
    }
    return false;
}

int	 raStream::GetPosition(void)
{
    unsigned int currtime = 0;
    if(m_channel)
    {
        m_channel->getPosition(&currtime, FMOD_TIMEUNIT_MS);
    }
    return currtime;
}
int  raStream::GetLenght(void)
{
    unsigned int length = 0;
    if(m_channel)
    {
        m_sound->getLength(&length, FMOD_TIMEUNIT_MS);
    }
    return length;
}
bool raStream::SetChannelMix(float fleft, float fright, float rleft, float rright,
        float sleft, float sright, float center, float bass)
{
    if(!m_channel) return false;

     FMOD_RESULT result = m_channel->setSpeakerMix(fleft, fright, center, bass, rleft, rright, sleft, sright);
     if(!ERRCHECK(result, "SetChannelMix")) return false;

     return true;
}
bool  raStream::SetPosition(unsigned int pos)
{
    if(!m_channel) return false;

    FMOD_RESULT result = m_channel->setPosition(pos, FMOD_TIMEUNIT_MS);
    if(!ERRCHECK(result, "SetPosition")) return false;

     return true;
}
void raStream::SetVolume(float vol)
{
    m_channel->setVolume(vol);
}
const char* raStream::GetTag(const char* Name, int Index)
{
    FMOD_TAG mftag;

    if (m_sound->getTag(Name, Index, &mftag) == FMOD_OK)
    {
        return (const char*)mftag.data;

    }

    return "";
}
bool raStream::ERRCHECK(FMOD_RESULT result, const char* Func)
{
    if (result != FMOD_OK)
    {
        std:: cout << "FMOD "<< result << " " << FMOD_ErrorString(result) << " "  << Func << std::endl;
        return false;
    }
    return true;
}
