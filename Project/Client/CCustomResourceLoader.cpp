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

	pShader->AddTexParam(TEX_0, "BML TEX");
	pShader->AddTexParam(TEX_1, "BM TEX");
	pShader->AddTexParam(TEX_2, "CMM TEX");
	pShader->AddTexParam(TEX_3, "NM TEX");
	pShader->AddTexParam(TEX_4, "EM TEX");
	pShader->AddTexParam(TEX_5, "RMT TEX");
	pShader->AddTexParam(TEX_6, "FM TEX");
	pShader->AddTexParam(TEX_7, "XM TEX");

	pShader->SetName(L"SkinningShader");
	CResMgr::GetInst()->AddRes(L"SkinningShader", pShader);
}

void LoadCustomResources()
{
	LoadCustomShader();

	//CModel::LoadFromFbx(L"model\\anjanath_tail.fbx");
	//CModel::LoadFromFbx(L"model\\anjanath_body_w_Anim.fbx");
	//CModel::LoadFromFbx(L"model\\Character Running.fbx");
	//CModel::LoadFromFbx(L"model\\Monster.fbx");
}
