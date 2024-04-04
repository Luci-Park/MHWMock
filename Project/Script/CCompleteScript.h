#pragma once
#include <Engine\CScript.h>

class CCompleteScript :
    public CScript
{
private:
    Ptr<CTexture>    m_Tex;
    bool                 m_bFadeIn;
    bool                 m_bUseObj;
    bool                 m_bIsPlayed;
    float                 m_fAlpha;


public:
    virtual void begin() override;
    virtual void tick() override;

public:
    void FadeIn();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CCompleteScript);
public:

    CCompleteScript();
    ~CCompleteScript();
};

