#pragma once
#include "ObjectInfoUI.h"

class CGameObject;

class ObjectLayerUI : public ObjectInfoUI
{
public:
    virtual int render_update() override;
public:
    ObjectLayerUI();
    ~ObjectLayerUI();
};

