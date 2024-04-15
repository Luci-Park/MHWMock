#pragma once
#include <Engine\CScript.h>

class CMonsterScript :
    public CScript
{
private:

public:
    virtual void update() override;
    virtual void OnCollisionEnter(CCollider3D* _Other) override;

    CLONE(CMonsterScript);
public:
    CMonsterScript();
    ~CMonsterScript();
};


