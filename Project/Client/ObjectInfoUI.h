#pragma once
#include "UI.h"

#include <Engine\ptr.h>
#include <Engine\CRes.h>

class CGameObject;

class ObjectInfoUI :
    public UI
{
private:
    CGameObject* m_Target;
    const OBJINFO_TYPE    m_Type;

public:
    void SetTarget(CGameObject* _Target);

    CGameObject* GetTarget() { return m_Target; }

    OBJINFO_TYPE GetObjInfoType() { return m_Type; }

public:
    virtual int render_update() override;


public:
    ObjectInfoUI(const string& _Name, OBJINFO_TYPE _Type);
    ~ObjectInfoUI();
};

