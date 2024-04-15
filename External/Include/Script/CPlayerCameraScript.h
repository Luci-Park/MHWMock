#pragma once
#include <Engine\CScript.h>

class CPlayerCameraScript :
    public CScript
{
private:
    CGameObject*        m_pTargetObj;
    float                     m_fRadius;
    float                     m_fRotationSpeed;

public:
    virtual void begin() override;
    virtual void update() override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CPlayerCameraScript);

public:
    CPlayerCameraScript();
    ~CPlayerCameraScript();
};

