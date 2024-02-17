#pragma once
#include "ComponentUI.h"
class Collider3DUI :
    public ComponentUI
{
private:
    bool    _Gravity;
public:
    virtual int render_update() override;

public:
    Collider3DUI();
    ~Collider3DUI();
};

