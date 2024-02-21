#pragma once
#include "ComponentUI.h"
class Collider3DUI :
    public ComponentUI
{
private:
    Vec3    _ScaleVec;
    Vec3    _HalfExtents;
    bool    _Gravity;
    bool    _EditSize;
    float   _Radius;
    float   _HalfHeight;
    bool    _GravityFlag;
public:
    virtual int render_update() override;

public:
    Collider3DUI();
    ~Collider3DUI();
};

