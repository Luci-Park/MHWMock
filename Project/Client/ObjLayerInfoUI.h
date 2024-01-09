#pragma once
#include "ObjectInfoUI.h"

class CGameObject;

class ObjLayerInfoUI : public ObjectInfoUI
{
public:
    virtual int render_update() override;
public:
    ObjLayerInfoUI();
    ~ObjLayerInfoUI();
};

