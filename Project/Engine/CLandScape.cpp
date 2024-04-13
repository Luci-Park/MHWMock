#include "pch.h"
#include "CLandScape.h"

#include "CRenderMgr.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CTransform.h"

CLandScape::CLandScape()
	: CRenderComponent(COMPONENT_TYPE::LANDSCAPE)
	, m_iFaceX(1)
	, m_iFaceZ(1)
{
	CreateMesh();
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"LandScapeMtrl"));
	
	// 알맞은 Texture넣어주기
	//m_HeightMap = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\tile\\DXT1_gnd02_soil_17_BML.dds");

	m_pTileArrTex = CResMgr::GetInst()->FindRes<CTexture>(L"texture\\tile\\TILE_ARRR.dds");
	m_pTileArrTex->GenerateMip(8);
}

CLandScape::~CLandScape()
{

}

void CLandScape::finaltick()
{

}

void CLandScape::render()
{
	if (GetMesh() == nullptr || GetMaterial() == nullptr)
		return;

	Transform()->UpdateData();

	GetMaterial()->SetScalarParam(INT_0, &m_iFaceX);
	GetMaterial()->SetScalarParam(INT_1, &m_iFaceZ);
	GetMaterial()->SetTexParam(TEX_2, m_HeightMap);

	//Vec2 vResolution = Vec2(m_HeightMap->Width(), m_HeightMap->Height());
	//GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_0, &vResolution);
	//GetMaterial()->SetTexParam(TEX_PARAM::TEX_2, m_HeightMap);

	//// 가중치 버퍼 해상도 전달
	//Vec2 vWeightMapResolution = Vec2((float)m_iWeightWidth, (float)m_iWeightHeight);
	//GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_1, &vWeightMapResolution);

	// 타일 배열 개수 전달
	float m_fTileCount = float(m_pTileArrTex->GetArraySize() / 2); // 색상, 노말 합쳐져있어서 나누기 2 해줌
	GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, &m_fTileCount);

	// 타일 텍스쳐 전달
	GetMaterial()->SetTexParam(TEX_PARAM::TEX_ARR_0, m_pTileArrTex);

	// Camera World Pos 전달
	Vec3 vCamWorldPos = CRenderMgr::GetInst()->GetMainCam()->Transform()->GetWorldPos();
	GetMaterial()->SetScalarParam(VEC4_0, &vCamWorldPos);


	// 재질 바인딩(업데이트)
	GetMaterial()->UpdateData();

	// 렌더
	GetMesh()->render();
}

void CLandScape::SetFace(UINT _iFaceX, UINT _iFaceZ)
{
	m_iFaceX = _iFaceX;
	m_iFaceZ = _iFaceZ;

	CreateMesh();
}

void CLandScape::CreateMesh()
{
	Vtx v;
	vector<Vtx> vecVtx;

	for (int i = 0; i < m_iFaceZ + 1; ++i)
	{
		for (int j = 0; j < m_iFaceX + 1; ++j)
		{

			v.vPos = Vec3(j, 0.f, i);
			v.vUV = Vec2((float)j, (float)m_iFaceZ - i);
			v.vTangent = Vec3(1.f, 0.f, 0.f);
			v.vNormal = Vec3(0.f, 1.f, 0.f);
			v.vBinormal = Vec3(0.f, 0.f, -1.f);
			v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);

			vecVtx.push_back(v);
		}
	}

	vector<UINT> vecIdx;

	for (int i = 0; i < m_iFaceZ; ++i)
	{
		for (int j = 0; j < m_iFaceX; ++j)
		{
			// 0
			// | \
			// 2--1  
			vecIdx.push_back((m_iFaceX + 1) * (i + 1) + (j));
			vecIdx.push_back((m_iFaceX + 1) * (i)+(j + 1));
			vecIdx.push_back((m_iFaceX + 1) * (i)+(j));

			// 0--1
			//  \ |
			//    2
			vecIdx.push_back((m_iFaceX + 1) * (i + 1) + (j));
			vecIdx.push_back((m_iFaceX + 1) * (i + 1) + (j + 1));
			vecIdx.push_back((m_iFaceX + 1) * (i)+(j + 1));
		}
	}

	Ptr<CMesh> pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	SetMesh(pMesh);

	// Mesh 재설정하고 나면 재질이 날라가기 때문에 다시 설정
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"LandScapeMtrl"));
}