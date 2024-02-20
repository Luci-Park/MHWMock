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
#include <Script\CDamageScript.h>

#include "CLevelSaveLoad.h"


#include <Engine/CSetColorShader.h>

#include <Engine\CCanvas.h>


void CreateTestLevel()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);
	pCurLevel->SetName(L"TestLevel");

	// Layer �̸�����
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Tile");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"Monster");
	pCurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	pCurLevel->GetLayer(5)->SetName(L"MonsterProjectile");
	pCurLevel->GetLayer(31)->SetName(L"ViewPort UI");


	// Main Camera Object ����
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CCameraMoveScript);

	pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera �� ����
	pMainCam->Camera()->SetLayerMaskAll(true);	// ��� ���̾� üũ
	pMainCam->Camera()->SetLayerMask(31, false);// UI Layer �� ���������� �ʴ´�.
	pMainCam->Camera()->SetLayerMask(1, false);// UI Layer �� ���������� �ʴ´�.

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);

	// UI cameara
	CGameObject* pUICam = new CGameObject;
	pUICam->SetName(L"UICamera");

	pUICam->AddComponent(new CTransform);
	pUICam->AddComponent(new CCamera);

	pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pUICam->Camera()->SetCameraIndex(1);		// Sub ī�޶�� ����
	pUICam->Camera()->SetLayerMaskAll(false);
	pUICam->Camera()->SetLayerMask(31, true);	// 31�� ���̾ üũ

	SpawnGameObject(pUICam, Vec3(0.f, 0.f, 1.f), 31);

	CGameObject* ptestUI = new CGameObject;
	ptestUI->SetName(L"TestUI");

	ptestUI->AddComponent(new CTransform);
	ptestUI->AddComponent(new CCanvas);

	ptestUI->Transform()->SetRelativeScale(100.f, 100.f,100.f);
	ptestUI->Canvas()->SetUITexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Character.png"));

	SpawnGameObject(ptestUI, Vec3(0.f, 0.f, 0.f), 31);

	// SkyBox �߰�
	CGameObject* pSkyBox = new CGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);

	pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100));
	pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::SPHERE);
	pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\Sky01.png"));

	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);

	// ���� �߰�
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

	{

		wstring test = L"CDamageScript";
		CGameObject* sgPlayer = new CGameObject;
		sgPlayer->SetName(L"sgPlayer");
		sgPlayer->AddComponent(new CTransform);
		sgPlayer->AddComponent(new CMeshRender);
		sgPlayer->AddComponent(new CPlayerScript);
		sgPlayer->AddComponent(new CDamageScript);
		sgPlayer->GetScrip
		SpawnGameObject(sgPlayer, L"Player");

		//CGameObject* sgMonster = new CGameObject;
		//sgMonster->SetName(L"sgMonster");
		//sgMonster->AddComponent(new CTransform);
		//sgMonster->AddComponent(new CMeshRender);
		//SpawnGameObject(sgMonster, L"Monster");
	}

	//CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");

}

void testtick()
{

	DrawDebugSphere(Vec3(10, 10, 10), 1.f, Vec4(1, 1, 1, 1), Vec3(0, 0, 0));
	DrawDebugSphere(Vec3(-10, -10, -10), 1.f, Vec4(1, 1, 1, 1), Vec3(0, 0, 0));

	DrawDebugLine(Vec3(10, 10, 10), Vec3(-10, -10, -10));
}
