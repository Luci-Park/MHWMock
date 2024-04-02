#pragma once
#include <Engine\CScript.h>

class CIntroObjScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

private:
    void Shoot();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CIntroObjScript);
public:

    CIntroObjScript();
    ~CIntroObjScript();
};

