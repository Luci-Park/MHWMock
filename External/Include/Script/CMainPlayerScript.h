#pragma once
#include "Engine\CScript.h"
#include "Engine\CGameObject.h"

class CMainPlayerScript :
    public CScript
{
public:
    enum class OBJPARAMNAME
    {
        BODYCOLLIDER,
        End,
    };
private:
    CGameObject* _BodyCollider;
    bool _Gravity;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void OnCollisionEnter(CCollider3D* _Other) override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CMainPlayerScript);
public:
    void UpdateTransform(PxTransform tr);
public:
    CMainPlayerScript();
    ~CMainPlayerScript();
};

