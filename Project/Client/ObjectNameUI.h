#pragma once
#include "ObjectInfoUI.h"

class CGameObject;

<<<<<<<< HEAD:Project/Client/ObjLayerInfoUI.h
class ObjLayerInfoUI : public ObjectInfoUI
========
class ObjectNameUI : public ObjectInfoUI
>>>>>>>> 93f5de6 (feat : Add ObjectNameUI):Project/Client/ObjectNameUI.h
{
public:
    virtual int render_update() override;
public:
<<<<<<<< HEAD:Project/Client/ObjLayerInfoUI.h
    ObjLayerInfoUI();
    ~ObjLayerInfoUI();
========
    ObjectNameUI();
    ~ObjectNameUI();
>>>>>>>> 93f5de6 (feat : Add ObjectNameUI):Project/Client/ObjectNameUI.h
};

