#pragma once
#include <Engine\CScript.h>

class CPlayerScript :
    public CScript
{
private:
    float           m_fSpeed;
    Ptr<CTexture>   m_pPlayerTexture;
    CGameObject*    m_pTargetObj;

public:
    virtual void begin() override;
    virtual void update() override;

    virtual void OnCollisionEnter(CCollider3D* _Other) override;

private:
    void Shoot();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};

