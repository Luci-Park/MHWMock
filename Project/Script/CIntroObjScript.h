#pragma once
#include <Engine\CScript.h>

class CIntroObjScript :
    public CScript
{
    enum class eStatus
    {
        FadeIn,
        FadeOut,
        None,
    };

private:
    eStatus     m_Status;
    float       m_fTime;
    float       m_fAlpha;
    float       m_fDuration;
    int          m_TexIdx;


    vector<Ptr<CTexture>>   m_vecTex;

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    void FadeIn();
    void FadeOut();
    void NormalState();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CIntroObjScript);
public:

    CIntroObjScript();
    ~CIntroObjScript();
};

