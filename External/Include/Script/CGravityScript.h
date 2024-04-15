#pragma once
#include <Engine\CScript.h>
class CGravityScript :
    public CScript
{
public:
    virtual void update() override;

private:
    CLONE(CGravityScript);
public:
    CGravityScript();
    ~CGravityScript();
};

