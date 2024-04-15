#pragma once
#include "Engine\CScript.h"

class CTestScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void update() override;

    virtual void OnAnimationBegin(IAnimationState* _pState);
    virtual void OnAnimationEndStart(IAnimationState* _pState);
    virtual void OnAnimationEndFinished(IAnimationState* _pState);

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CTestScript);

    CTestScript();
    ~CTestScript();
};

