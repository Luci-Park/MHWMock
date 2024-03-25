#pragma once
#include "ComponentUI.h"
class Collider3DUI :
    public ComponentUI
{
private:
    Vec3    _ScaleVec;
    Vec3    _HalfExtents;
    Vec3    _OffSetPos;

    bool    _Gravity;
    bool    _EditSize;
    bool    _GravityFlag;
    
    float   _Radius;
    float   _HalfHeight;
public:
    virtual int render_update() override;

public:
    Collider3DUI();
    ~Collider3DUI();
};

