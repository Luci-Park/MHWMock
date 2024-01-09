#pragma once
#include "CRenderComponent.h"

class CDecal :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_DecalTex;

    bool            m_bDeferred;
    bool            m_bEmissive;


public:
    // Decal �������� ������ ���� �� ������ �ƴ���
    void SetDeferredDecal(bool _bDeferred);

    // ��Į�� �������� ����Ұ����� �ƴ���
    void ActivateEmissive(bool _bActivate) { m_bEmissive = _bActivate; }

public:
    virtual void finaltick() override;
    virtual void render() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CDecal);
public:
    CDecal();
    ~CDecal();
};

