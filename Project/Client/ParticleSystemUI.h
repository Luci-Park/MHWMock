#pragma once
#include "ComponentUI.h"
class ParticleSystemUI :
    public ComponentUI
{

public:
    virtual int render_update() override;
    void SelectTexture(DWORD_PTR _Key);

public:
    ParticleSystemUI();
    ~ParticleSystemUI();
};

