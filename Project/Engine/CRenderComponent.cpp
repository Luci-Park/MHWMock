#include "pch.h"
#include "CRenderComponent.h"

#include "CTransform.h"

#include "CResMgr.h"
#include "CMaterial.h"

CRenderComponent::CRenderComponent(COMPONENT_TYPE _type)
	: CComponent(_type)
	, m_bFrustumCheck(true)
{
}

CRenderComponent::CRenderComponent(const CRenderComponent& _origin)
	: CComponent(_origin)
	, m_pMesh(_origin.m_pMesh)
	, m_bFrustumCheck(_origin.m_bFrustumCheck)
	, m_pCurrentMtrl(_origin.m_pCurrentMtrl)
	, m_pSharedMtrl(_origin.m_pCurrentMtrl)
	, m_pDynamicMtrl(nullptr)
{
}

CRenderComponent::~CRenderComponent()
{
}

void CRenderComponent::render_shadowmap()
{
	if (GetMesh() == nullptr || GetMaterial() == nullptr) return;
	Ptr<CMaterial> pShadowMapMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ShadowMapMtrl");

	Transform()->UpdateData();

	pShadowMapMtrl->UpdateData();

	GetMesh()->render();
}

void CRenderComponent::SetMaterial(Ptr<CMaterial> _Mtrl)
{
	m_pSharedMtrl = _Mtrl;
	m_pCurrentMtrl = m_pSharedMtrl;
}

Ptr<CMaterial> CRenderComponent::GetSharedMaterial()
{
	if (m_pCurrentMtrl != m_pSharedMtrl)
	{
		m_pCurrentMtrl = m_pSharedMtrl;
		m_pDynamicMtrl = nullptr;
	}

	return m_pSharedMtrl;
}

Ptr<CMaterial> CRenderComponent::GetDynamicMaterial()
{
	// 원본 재질이 없다 -> Nullptr 반환
	if (nullptr == m_pSharedMtrl)
	{
		m_pCurrentMtrl = nullptr;
		return m_pCurrentMtrl;
	}

	// 동적 재질 최초 요청시 제작 해서 준다.
	if (nullptr == m_pDynamicMtrl)
	{		
		m_pDynamicMtrl = m_pSharedMtrl->Clone();		
	}

	// 동적 재질을 현재 사용재질로 지정한다.
	m_pCurrentMtrl = m_pDynamicMtrl;


	return m_pCurrentMtrl;
}

void CRenderComponent::SaveToLevelFile(FILE* _File)
{
	SaveResRef(m_pMesh.Get(), _File);
	SaveResRef(m_pSharedMtrl.Get(), _File);	
}

void CRenderComponent::LoadFromLevelFile(FILE* _File)
{
	LoadResRef(m_pMesh, _File);
	LoadResRef(m_pSharedMtrl, _File);

	SetMaterial(m_pSharedMtrl);
}
