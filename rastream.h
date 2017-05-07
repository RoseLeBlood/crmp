#ifndef RASTREAM_H
#define RASTREAM_H

#include <fmodex/fmod.hpp>
#include <string>

#include "rasystem.h"
#define raString std::string

class  IRATag
{
public:
    IRATag(raString data, raString name) : m_data(data), m_name(name) { }
    ~IRATag() { }

    raString GetValue()                  { return m_data; }
    raString GetName()                   { return m_name; }

    void SetValue(std::string value) { m_data = value; }
    void GetValue(std::string value) { m_name = value; }
private:
    raString	m_data;
    raString	m_name;
};

struct raVector3
{
    float x,y,z;

    inline raVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)        { }
    inline raVector3(float xyz) : x(xyz), y(xyz), z(xyz)                        { }
    inline raVector3() : x(0), y(0), z(0)                                       { }
};

class  raStream
{
public:
    static raStream& Instance()
    {
        if(m_instance == NULL)
            m_instance = new raStream();

        return *m_instance;
    }

    virtual bool Create(raSystem* AudioSystem);
    virtual void Destroy();

    virtual void Set3DMinMaxDistance(float min, float max);
    virtual bool SetVelocity(raVector3& vec);
    virtual bool Set3DPosition(raVector3& vec);

    virtual int	 GetPosition(void);
    virtual bool SetPosition(unsigned int pos);
    virtual int  GetLenght(void);

    virtual bool SetChannelMix(float fleft, float fright, float rleft, float rright,
        float sleft, float sright, float center, float bass);

    virtual void SetVolume(float vol);

    virtual bool LoadStream(const char* FileName, bool b3D = true);
    virtual bool CloseStream();
    virtual bool PlayStream(raVector3 Position, raVector3 Velocity, float minDistance = 1.0f,
        float maxDistance = 100.0f);
    virtual bool PauseStream();
    virtual bool StopStream();

    virtual const char *GetTag(const char *Name, int Index);

    FMOD::Sound*    GetSoune()      { return m_sound; }
    FMOD::Channel*  GetChannel()    { return m_channel; }
    FMOD::System*   GetSystem()     { return m_system->GetSystem(); }

    bool            IsPlaying()     { if(!m_channel) return false; bool playing = false; m_channel->isPlaying(&playing); return playing; }

protected:
    bool ERRCHECK(FMOD_RESULT result, const char *Func = "");
protected:
    FMOD::Sound							*m_sound;
    FMOD::Channel						*m_channel;
    raSystem                           *m_system;
protected:
    raStream() { }
    static raStream* m_instance;
};

#endif // RASTREAM_H
