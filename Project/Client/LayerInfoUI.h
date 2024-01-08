#pragma once
#include "ObjectInfoUI.h"

class CGameObject;

class LayerInfoUI : public ObjectInfoUI
{
public:
    virtual int render_update() override;
public:
    LayerInfoUI();
    ~LayerInfoUI();
};

