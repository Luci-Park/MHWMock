#pragma once
#include "CRenderComponent.h"
#include "CGameObject.h"

class CCanvas :
    public CRenderComponent
{
private:
    // 0 : non_use
    // 1 : FadeOption
    // 2 : AlphaOption
    int                  m_bUseAlpha;
    float               m_fAlpha;
 
    Ptr<CTexture>   m_UITex;

public:
    void SetAlpha(float _Alpha) { m_fAlpha = _Alpha; }
    void SetUseAlpha(int _UseAlpha) { m_bUseAlpha = _UseAlpha; }

public:
    float GetAlpha() { return m_fAlpha; }
    int GetUseAlpha() { return m_bUseAlpha; }

public:
    virtual void finaltick() override;
    virtual void render() override;

public:
    virtual void SaveToLevelFile(FILE* _File);
    virtual void LoadFromLevelFile(FILE* _FILE);

    CLONE(CCanvas);
public:
    void SetUITexture(Ptr<CTexture> _Tex);
public:
    Ptr<CTexture> GetUITexture() { return m_UITex; }
public:
    CCanvas();
    ~CCanvas();
};

