#pragma once
#include "ComponentUI.h"
class Collider3DUI :
    public ComponentUI
{
private:
    Vec3    _ScaleVec;
    bool    _Gravity;
    bool    _EditSize;
public:
    virtual int render_update() override;

public:
    Collider3DUI();
    ~Collider3DUI();
};

