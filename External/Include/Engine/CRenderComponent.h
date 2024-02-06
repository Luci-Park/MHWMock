#pragma once
#include "CComponent.h"


#include "CMesh.h"
#include "CMaterial.h"

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>              m_pMesh;

    Ptr<CMaterial>          m_pSharedMtrl;  // ���� ���׸���
    Ptr<CMaterial>          m_pDynamicMtrl; // SharedMaterial ���纻
    Ptr<CMaterial>          m_pCurrentMtrl; // ���� ��� ���� ����

    bool                    m_bFrustumCheck;

public:
    virtual void render() = 0;
    void render_shadowmap();

public:
    void SetFrustumCheck(bool _Check) { m_bFrustumCheck = _Check; }

    virtual void SetMesh(Ptr<CMesh> _Mesh) { m_pMesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Mtrl);

    Ptr<CMesh> GetMesh() { return m_pMesh; }
    Ptr<CMaterial> GetMaterial() { return m_pCurrentMtrl; }
    Ptr<CMaterial> GetSharedMaterial();
    Ptr<CMaterial> GetDynamicMaterial();


    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    bool IsFrustumCheck() { return m_bFrustumCheck; }

public:
    CRenderComponent(COMPONENT_TYPE _type);
    CRenderComponent(const CRenderComponent& _origin);
    ~CRenderComponent();
};

