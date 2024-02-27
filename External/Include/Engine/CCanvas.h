#pragma once
#include "CRenderComponent.h"
#include "CGameObject.h"

class CCanvas :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_UITex;
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

