#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>

#include <Script\CPlayerScript.h>
#include <Script\CMonsterScript.h>
#include <Script/CCameraMoveScript.h>

#include "CLevelSaveLoad.h"


#include <Engine/CSetColorShader.h>

#include <Engine\CCanvas.h>


void CreateTestLevel()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);
	pCurLevel->SetName(L"TestLevel");

	/*pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Tile");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"Monster");
	pCurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	pCurLevel->GetLayer(5)->SetName(L"MonsterProjectile");
	pCurLevel->GetLayer(15)->SetName(L"ViewPort UI");*/

	//CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");

	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);

	pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pMainCam->Camera()->SetCameraIndex(0);		
	pMainCam->Camera()->SetLayerMaskAll(true);	
	pMainCam->Camera()->SetLayerMask(15, false);
	pMainCam->Camera()->SetLayerMask(1, false);

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);

	// UI cameara
	CGameObject* pUICam = new CGameObject;
	pUICam->SetName(L"UICamera");

	pUICam->AddComponent(new CTransform);
	pUICam->AddComponent(new CCamera);

	pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pUICam->Camera()->SetCameraIndex(1);		
	pUICam->Camera()->SetLayerMaskAll(false);
	pUICam->Camera()->SetLayerMask(15, true);	

	SpawnGameObject(pUICam, Vec3(0.f, 0.f, 1.f), 15);

	//CGameObject* ptestUI = new CGameObject;
	//ptestUI->SetName(L"TestUI");

	//ptestUI->AddComponent(new CTransform);
	//ptestUI->AddComponent(new CCanvas);

	//ptestUI->Transform()->SetRelativeScale(100.f, 100.f,100.f);
	//ptestUI->Canvas()->SetUITexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Character.png"));

	//SpawnGameObject(ptestUI, Vec3(0.f, 0.f, 0.f), 31);

	CGameObject* pSkyBox = new CGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);

	pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100));
	pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::SPHERE);
	pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\Sky01.png"));

	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);

	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"Directional Light");

	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight3D);

	pLightObj->Transform()->SetRelativeRot(Vec3(XM_PI / 4.f, XM_PI / 4.f, 0.f));
	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light3D()->SetRadius(500.f);
	pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLightObj->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));

	SpawnGameObject(pLightObj, Vec3(-2000, 2000.f, -2000.f), 0);

	//CGameObject* pParentObj = new CGameObject;
	//pParentObj->SetName(L"Parent");
	//pParentObj->AddComponent(new CTransform);
	//pParentObj->AddComponent(new CMeshRender);
	//pParentObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//pParentObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
	//
	//CGameObject* pChildObj = new CGameObject;
	//pChildObj->SetName(L"Child");
	//pChildObj->AddComponent(new CTransform);
	//pChildObj->AddComponent(new CMeshRender);
	//pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
	//pParentObj->AddChild(pChildObj);
	//
	//SpawnGameObject(pParentObj);
	// ������Ʈ ����
	//CGameObject* pObject = new CGameObject;
	//pObject->SetName(L"Player");
	//pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CMeshRender);
	//pObject->AddComponent(new CPlayerScript);
	//SpawnGameObject(pObject);
	// LandScape Object
	//CGameObject* pLandScape = new CGameObject;
	//pLandScape->SetName(L"LandScape");
	//
	//pLandScape->AddComponent(new CTransform);
	//pLandScape->AddComponent(new CLandScape);
	//
	//pLandScape->Transform()->SetRelativeScale(Vec3(200.f, 1000.f, 200.f));
	//
	//pLandScape->LandScape()->SetFace(32, 32);
	//pLandScape->LandScape()->SetFrustumCheck(false);
	//pLandScape->LandScape()->SetHeightMap(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HeightMap_01.jpg"));
	//pLandScape->LandScape()->GetMaterial()->GetShader()->SetRSType(RS_TYPE::WIRE_FRAME);
	//
	//SpawnGameObject(pLandScape, Vec3(0.f, 0.f, 0.f), 0);

	// LandScape Object
	//CGameObject* pLandScape = new CGameObject;
	//pLandScape->SetName(L"LandScape");
	//
	//pLandScape->AddComponent(new CTransform);
	//pLandScape->AddComponent(new CLandScape);
	//
	//pLandScape->Transform()->SetRelativeScale(Vec3(200.f, 1000.f, 200.f));
	//
	//pLandScape->LandScape()->SetFace(32, 32);
	//pLandScape->LandScape()->SetFrustumCheck(false);
	//pLandScape->LandScape()->SetHeightMap(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HeightMap_01.jpg"));
	//pLandScape->LandScape()->GetMaterial()->GetShader()->SetRSType(RS_TYPE::WIRE_FRAME);
	//
	//SpawnGameObject(pLandScape, Vec3(0.f, 0.f, 0.f), 0);

	//Ptr<CModel> model = CResMgr::GetInst()->FindRes<CModel>(L"model\\playerMerge_W_Animation\\playerMerge_W_Animation.model");
	//auto gc = model->CreateGameObjectFromModel();
	//Ptr<CAnimationClip> clip = CResMgr::GetInst()->FindRes<CAnimationClip>(L"model\\playerMerge_W_Animation\\anim\\Animation 118.anim");
	//double percent = 100;
	//clip = gc->Animator3D()->GetCurrentAnimation(percent);



	CGameObject* pObject1 = new CGameObject;
	pObject1->SetName(L"Player1");
	pObject1->AddComponent(new CTransform);
	pObject1->AddComponent(new CMeshRender);
	pObject1->AddComponent(new CPlayerScript);
	pObject1->Transform()->SetRelativeScale(Vector3(100.f, 100.f, 100.f));

	pObject1->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	pObject1->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
	SpawnGameObject(pObject1, Vec3(0.f, 0.f, 0.f), 2);


	CGameObject* pObject2 = new CGameObject;
	pObject2->SetName(L"Player2");
	pObject2->AddComponent(new CTransform);
	pObject2->AddComponent(new CMeshRender);
	pObject2->Transform()->SetRelativeScale(Vector3(100.f, 100.f, 100.f));
	pObject2->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	pObject2->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
	SpawnGameObject(pObject2, Vec3(50.f, 0.f, 0.f), 3);
}

void testtick()
{

	DrawDebugSphere(Vec3(10, 10, 10), 1.f, Vec4(1, 1, 1, 1), Vec3(0, 0, 0));
	DrawDebugSphere(Vec3(-10, -10, -10), 1.f, Vec4(1, 1, 1, 1), Vec3(0, 0, 0));

	DrawDebugLine(Vec3(10, 10, 10), Vec3(-10, -10, -10));
}
