#ifndef RASYSTEM_H
#define RASYSTEM_H

#include <fmodex/fmod.hpp>
#include <fmodex/fmod_errors.h>
#include <fmodex/fmod_dsp.h>

#include "crmpsettings.h"


class raSystem
{
public:
    raSystem();
    virtual ~raSystem();

    virtual bool Create();
    virtual void Update();

    FMOD::System*   GetSystem()  { return m_system; }



private:
    bool ERRCHECK(FMOD_RESULT result, const char *Func ="");
    void plotinfo();
private:
    FMOD::System*				m_system;
};

#endif // RASYSTEM_H
