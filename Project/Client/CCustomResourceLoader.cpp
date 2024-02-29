#include "pch.h"
#include "CCustomResourceLoader.h"
#include <Engine/CGraphicsShader.h>
#include <Engine/CComputeShader.h>
#include <Engine/CResMgr.h>

void LoadCustomShader()
{
	// ============================
	// Skinning
	// RS_TYPE : CULL_NONE
	// DS_TYPE : LESS
	// BS_TYPE : DEFAULT	 
	// Domain : MASK
	// ============================
	Ptr<CGraphicsShader> pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\skinning.fx", "vert");
	pShader->CreatePixelShader(L"shader\\skinning.fx", "frag");
	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEFERRED);
	pShader->SetName(L"SkinningShader");

	CResMgr::GetInst()->AddRes(L"SkinningShader", pShader);
}

void LoadCustomResources()
{
	LoadCustomShader();

	//CModel::LoadFromFbx(L"model\\anjanath_tail.fbx");
	//CModel::LoadFromFbx(L"model\\Character Running.fbx");
	//CModel::LoadFromFbx(L"model\\Monster.fbx");
}
