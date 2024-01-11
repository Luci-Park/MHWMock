#pragma once
#include "ObjectInfoUI.h"

class CGameObject;

class ObjLayerInfoUI : public ObjectInfoUI
{
private:
    char* items[MAX_LAYER];
    char* combo_preview_value;
    bool is_selected;

    int item_current_idx;

public:
    virtual int render_update() override;
public:
    ObjLayerInfoUI();
    ~ObjLayerInfoUI();

};

