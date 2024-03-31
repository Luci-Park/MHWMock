#include "pch.h"
#include "CEditorObjMgr.h"

#include "CGameObjectEx.h"
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CRenderMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CTimeMgr.h>
#include <Engine\CKeyMgr.h>

#include <Script\CCameraMoveScript.h>

CEditorObjMgr::CEditorObjMgr()
	: m_DebugShape{}
	, m_bUseDebugObj (true)
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
	m_DebugShape[(UINT)SHAPE_TYPE::CUBE]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeCubeMtrl"));

	m_DebugShape[(UINT)SHAPE_TYPE::CAPSULE] = new CGameObjectEx;
	m_DebugShape[(UINT)SHAPE_TYPE::CAPSULE]->AddComponent(new CTransform);
	m_DebugShape[(UINT)SHAPE_TYPE::CAPSULE]->AddComponent(new CMeshRender);
	m_DebugShape[(UINT)SHAPE_TYPE::CAPSULE]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CapsuleMesh"));
	m_DebugShape[(UINT)SHAPE_TYPE::CAPSULE]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeCapsuleMtrl"));

	m_DebugShape[(UINT)SHAPE_TYPE::CONVEX]= new CGameObjectEx;
	m_DebugShape[(UINT)SHAPE_TYPE::CONVEX]->AddComponent(new CTransform);
	m_DebugShape[(UINT)SHAPE_TYPE::CONVEX]->AddComponent(new CMeshRender);
	m_DebugShape[(UINT)SHAPE_TYPE::CONVEX]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeMtrl"));

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
	pEditorCamObj->Transform()->SetRelativePos(0, 0, -50000);

	pEditorCamObj->Camera()->SetFar(100000.f);
	pEditorCamObj->Camera()->SetLayerMaskAll(true);
	pEditorCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pEditorCamObj->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);


	m_vecEditorObj.push_back(pEditorCamObj);
	CRenderMgr::GetInst()->RegisterEditorCamera(pEditorCamObj->Camera());
}



void CEditorObjMgr::progress()
{
	CLevel* pCulLeve = CLevelMgr::GetInst()->GetCurLevel();
	LEVEL_STATE eLevelStat = pCulLeve->GetState();

	if (eLevelStat != LEVEL_STATE::STOP)
		return;


	if (CKeyMgr::GetInst()->GetKeyState(KEY::L) == KEY_STATE::TAP)
	{
		if (m_bUseDebugObj)
			m_bUseDebugObj = false;
		else
			m_bUseDebugObj = true;
	}

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

	if (!m_bUseDebugObj)
		return;

	// DebugShape Render
	CGameObjectEx* pShapeObj = nullptr;

	vector<tDebugShapeInfo3D>::iterator iter = m_DebugShapeInfo3D.begin();
	int iConvexMeshCnt = 0;

	for (; iter != m_DebugShapeInfo3D.end();)
	{
		switch (iter->eShape)
		{
		case SHAPE_TYPE::RECT:
			pShapeObj = m_DebugShape[(UINT)SHAPE_TYPE::RECT];
			break;
		case SHAPE_TYPE::CIRCLE:
			pShapeObj = m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE];
			break;
		case SHAPE_TYPE::CUBE:
			pShapeObj = m_DebugShape[(UINT)SHAPE_TYPE::CUBE];
			pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &iter->vHalfExtents.x);
			pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_1, &iter->vHalfExtents.y);
			pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_2, &iter->vHalfExtents.z);
			break;
		case SHAPE_TYPE::CAPSULE:
			pShapeObj = m_DebugShape[(UINT)SHAPE_TYPE::CAPSULE];
			pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &iter->fRadius);
			pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_1, &iter->fHalfHeight);
			break;
		case SHAPE_TYPE::SPHERE:
			pShapeObj = m_DebugShape[(UINT)SHAPE_TYPE::SPHERE];
			break;
		case SHAPE_TYPE::CONVEX:
			pShapeObj = m_DebugShape[(UINT)SHAPE_TYPE::CONVEX];
			pShapeObj->MeshRender()->SetMesh(m_DebugShapeMesh3D[iConvexMeshCnt]);
			pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, &iter->vConvexScale.x);
			pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_1, &iter->vConvexScale.y);
			pShapeObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_2, &iter->vConvexScale.z);

			break;
		}

		if (iter->matWorld != XMMatrixIdentity())
		{
			//Vec3 pos = iter->matWorld.Translation();
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
			if (iter->eShape == SHAPE_TYPE::CONVEX)
				m_DebugShapeMesh3D.erase(m_DebugShapeMesh3D.begin() + iConvexMeshCnt);

			iter = m_DebugShapeInfo3D.erase(iter);
		}
		else
		{
			if(iter->eShape == SHAPE_TYPE::CONVEX)
				++iConvexMeshCnt;
			
			++iter;
		}

	}
}
