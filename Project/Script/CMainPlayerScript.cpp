#include "pch.h"
#include "CMainPlayerScript.h"
#include "Engine\CCollider3D.h"
#include "Engine\CKeyMgr.h"
#include "Engine\CAnimator3D.h"


CMainPlayerScript::CMainPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::MAINPLAYERSCRIPT)
	, _BodyCollider(nullptr)
	, _Gravity(true)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_BodyCollider, "BodyObj Obj");
}

CMainPlayerScript::~CMainPlayerScript()
{
}

void CMainPlayerScript::begin()
{
}

void CMainPlayerScript::tick()
{



	Vec3 vCurPos = Transform()->GetRelativePos();
	
	CCollider3D* coll = (CCollider3D*)_BodyCollider->GetComponent(COMPONENT_TYPE::COLLIDER3D);
	if (nullptr != coll)
	{
		PxTransform globalTr = coll->GetRigidActor()->getGlobalPose();
		Vec3 pos = Vec3(globalTr.p.x, globalTr.p.y, globalTr.p.z);
		UpdateTransform(globalTr);
	}
}

void CMainPlayerScript::OnCollisionEnter(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER_TYPE::Ground && _Gravity == true)
	{
		CCollider3D * coll = (CCollider3D*)GetOwner()->GetComponent(COMPONENT_TYPE::COLLIDER3D);
		coll->SetGravity(false);
		_Gravity = false;
	}
}

void CMainPlayerScript::UpdateTransform(PxTransform tr)
{
	Vec3 pos = Vec3(tr.p.x, tr.p.y, tr.p.z);
	Vec4 rot = Vec4(tr.q.x, tr.q.y, tr.q.z, tr.q.w);
	//GetOwner()->Transform()->SetRelativePos(pos);
}

void CMainPlayerScript::SaveToLevelFile(FILE* _File)
{
	SaveGameObjectParam(_BodyCollider, _File);
}

void CMainPlayerScript::LoadFromLevelFile(FILE* _FILE)
{
	LoadGameObjectParam((int)OBJPARAMNAME::BODYCOLLIDER, _FILE);
}
