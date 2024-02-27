#pragma once
#include "ComponentUI.h"
class CanvasUI :
    public ComponentUI
{
public:
    virtual int render_update() override;
public:
    CanvasUI();
    ~CanvasUI();
};

