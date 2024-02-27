#pragma once
#include "ComponentUI.h"
class CanvasUI :
    public ComponentUI
{
public:
    virtual int render_update() override;
public:
    void SelectMesh(DWORD_PTR _Key);
    void SelectMaterial(DWORD_PTR _Key);
    void SelectTexture(DWORD_PTR _Key);
public:
    CanvasUI();
    ~CanvasUI();
};

