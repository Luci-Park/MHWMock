#pragma once
#include "Engine\CScript.h"

class CMainPlayerScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void OnCollisionEnter(CCollider3D* _Other) override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CMainPlayerScript);
public:
    CMainPlayerScript();
    ~CMainPlayerScript();
};

