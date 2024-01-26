#include "pch.h"
#include "CCustomResourceLoader.h"

#include <Engine/ptr.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CComputeShader.h>
#include <Engine/CResMgr.h>

void LoadCustomShader()
{
	// ============================
	// TestShader
	// RS_TYPE : CULL_NONE
	// DS_TYPE : LESS
	// BS_TYPE : DEFAULT	 
	// Domain : MASK
	// ============================
	Ptr<CGraphicsShader> pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_TestShader");
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_TestShader");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);

	// Parameter
	pShader->AddScalarParam(INT_0, "Color Type");
	pShader->AddTexParam(TEX_0, "Output Texture");

	CResMgr::GetInst()->AddRes(L"TestCustomShader", pShader);
}

void LoadCustomResources()
{
	LoadCustomShader();

	CModel::LoadFromFbx(L"model\\anjanath_tail.fbx");
	CModel::LoadFromFbx(L"model\\Monster.fbx");
}
