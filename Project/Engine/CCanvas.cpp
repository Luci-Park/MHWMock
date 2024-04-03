#include "pch.h"
#include "CCanvas.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CLayer.h"

#include "CTransform.h"

#include "CResMgr.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "CRenderMgr.h"
#include "CMRT.h"

CCanvas::CCanvas()
	:CRenderComponent(COMPONENT_TYPE::CANVAS)
	, m_bUseAlpha(0)
{
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"CanvasMtrl"));
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	SetFrustumCheck(false);
}

CCanvas::~CCanvas()
{
	m_UITex = nullptr;
}

void CCanvas::finaltick()
{

}

void CCanvas::render()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	Transform()->UpdateData();

	if (nullptr != m_UITex)
	{
		GetMaterial()->SetTexParam(TEX_0, m_UITex);
	}
	GetMaterial()->SetScalarParam(INT_0, &m_bUseAlpha);
	GetMaterial()->SetScalarParam(FLOAT_0, &m_fAlpha);
	
	GetMaterial()->UpdateData();

	// ·»´õ
	GetMesh()->render();
}

void CCanvas::SaveToLevelFile(FILE* _File)
{
	CRenderComponent::SaveToLevelFile(_File);
	SaveResRef(m_UITex.Get(), _File);
}

void CCanvas::LoadFromLevelFile(FILE* _FILE)
{
	CRenderComponent::LoadFromLevelFile(_FILE);
	LoadResRef(m_UITex, _FILE);

	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"CanvasMtrl"));
	SetUITexture(m_UITex);
}

void CCanvas::SetUITexture(Ptr<CTexture> _Tex)
{
	m_UITex = _Tex;
}