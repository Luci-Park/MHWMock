#include "pch.h"
#include "CEditorObjMgr.h"

#include "CGameObjectEx.h"
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CRenderMgr.h>
#include <Engine\CTimeMgr.h>
#include <Engine\CKeyMgr.h>

#include <Script\CCameraMoveScript.h>

CEditorObjMgr::CEditorObjMgr()
	: m_DebugShape{}
{

}

CEditorObjMgr::~CEditorObjMgr()
{
	Safe_Del_Vec(m_vecEditorObj);
	Safe_Del_Array(m_DebugShape);
}

void CEditorObjMgr::init()
{
	// 디버그 쉐이프 생성
	m_DebugShape[(UINT)SHAPE_TYPE::RECT] = new CGameObjectEx;
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->AddComponent(new CTransform);
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->AddComponent(new CMeshRender);
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh_Debug"));
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeMtrl"));

	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE] = new CGameObjectEx;
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->AddComponent(new CTransform);
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->AddComponent(new CMeshRender);
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh_Debug"));
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeMtrl"));

	m_DebugShape[(UINT)SHAPE_TYPE::CUBE] = new CGameObjectEx;
	m_DebugShape[(UINT)SHAPE_TYPE::CUBE]->AddComponent(new CTransform);
	m_DebugShape[(UINT)SHAPE_TYPE::CUBE]->AddComponent(new CMeshRender);
	m_DebugShape[(UINT)SHAPE_TYPE::CUBE]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh_Debug"));
	m_DebugShape[(UINT)SHAPE_TYPE::CUBE]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeMtrl"));

	m_DebugShape[(UINT)SHAPE_TYPE::SPHERE] = new CGameObjectEx;
	m_DebugShape[(UINT)SHAPE_TYPE::SPHERE]->AddComponent(new CTransform);
	m_DebugShape[(UINT)SHAPE_TYPE::SPHERE]->AddComponent(new CMeshRender);
	m_DebugShape[(UINT)SHAPE_TYPE::SPHERE]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	m_DebugShape[(UINT)SHAPE_TYPE::SPHERE]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeSphereMtrl"));

	// EditorObject 생성
	CGameObjectEx* pEditorCamObj = new CGameObjectEx;
	pEditorCamObj->AddComponent(new CTransform);
	pEditorCamObj->AddComponent(new CCamera);
	pEditorCamObj->AddComponent(new CCameraMoveScript);

	pEditorCamObj->Camera()->SetFar(100000.f);
	pEditorCamObj->Camera()->SetLayerMaskAll(true);
	pEditorCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pEditorCamObj->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);


	m_vecEditorObj.push_back(pEditorCamObj);
	CRenderMgr::GetInst()->RegisterEditorCamera(pEditorCamObj->Camera());
}



void CEditorObjMgr::progress()
{
	// DebugShape 정보 가져오기
	vector<tDebugShapeInfo>& vecInfo = CRenderMgr::GetInst()->GetDebugShapeInfo();
	m_DebugShapeInfo.insert(m_DebugShapeInfo.end(), vecInfo.begin(), vecInfo.end());
	vecInfo.clear();

	// DebugShape 정보 가져오기
	vector<tDebugShapeInfo3D>& vecInfo3D = CRenderMgr::GetInst()->GetDebugShapeInfo3D();
	m_DebugShapeInfo3D.insert(m_DebugShapeInfo3D.end(), vecInfo3D.begin(), vecInfo3D.end());
	vecInfo3D.clear();

	vector<Ptr<CMesh>>& vecMesh3D = CRenderMgr::GetInst()->GetDebugShapeMesh3D();
	m_DebugShapeMesh3D.insert(m_DebugShapeMesh3D.end(), vecMesh3D.begin(), vecMesh3D.end());
	vecMesh3D.clear();
	
	tick();

	render();
}


void CEditorObjMgr::tick()
{
	for (size_t i = 0; i < m_vecEditorObj.size(); ++i)
	{
		m_vecEditorObj[i]->tick();
	}

	for (size_t i = 0; i < m_vecEditorObj.size(); ++i)
	{
		m_vecEditorObj[i]->finaltick();
	}
}

void CEditorObjMgr::render()
{
	for (size_t i = 0; i < m_vecEditorObj.size(); ++i)
	{
		m_vecEditorObj[i]->render();
	}


	// DebugShape Render
	CGameObjectEx* pShapeObj = nullptr;

	vector<tDebugShapeInfo3D>::iterator iter = m_DebugShapeInfo3D.begin();
	int cnt = 0;

	for (; iter != m_DebugShapeInfo3D.end();)
	{
		pShapeObj = new CGameObjectEx;
		pShapeObj->AddComponent(new CTransform);
		pShapeObj->AddComponent(new CMeshRender);
		pShapeObj->MeshRender()->SetMesh(m_DebugShapeMesh3D[cnt]);
		pShapeObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeMtrl"));

		if (iter->matWorld != XMMatrixIdentity())
		{
			pShapeObj->Transform()->SetWorldMat(iter->matWorld);
		}
		else
		{
			pShapeObj->Transform()->SetRelativePos(iter->vWorldPos);
			pShapeObj->Transform()->SetRelativeScale(iter->vWorldScale);
			pShapeObj->Transform()->SetRelativeRot(iter->vWorldRotation);
			pShapeObj->finaltick();
		}

		pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, &iter->vColor);
		
		if (iter->bDepthTest)
			pShapeObj->MeshRender()->GetMaterial()->GetShader()->SetDSType(DS_TYPE::LESS);
		else
			pShapeObj->MeshRender()->GetMaterial()->GetShader()->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);

		pShapeObj->render();

		iter->fCurTime += DT;
		if (iter->fMaxTime < iter->fCurTime)
		{
			iter = m_DebugShapeInfo3D.erase(iter);
			m_DebugShapeMesh3D.erase(m_DebugShapeMesh3D.begin() + cnt);
		}
		else
		{
			++iter;
			++cnt;
		}
	}
}
