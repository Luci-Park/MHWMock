#include "pch.h"
#include "CCanvas.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CLayer.h"

#include "CTransform.h"

#include "CResMgr.h"
#include "CMesh.h"
#include "CMaterial.h"

CCanvas::CCanvas()
	:CRenderComponent(COMPONENT_TYPE::CANVAS)
{
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"CanvasMtrl"));
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	SetFrustumCheck(false);
}

CCanvas::~CCanvas()
{

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

	GetMaterial()->UpdateData();
	// ·»´õ
	GetMesh()->render();
}

void CCanvas::SetUITexture(Ptr<CTexture> _Tex)
{
	m_UITex = _Tex;
}