#pragma once
#include "ObjectInfoUI.h"

class CGameObject;

class ObjNameInfoUI : public ObjectInfoUI
{
public:
    virtual int render_update() override;
public:
    ObjNameInfoUI();
    ~ObjNameInfoUI();
};

