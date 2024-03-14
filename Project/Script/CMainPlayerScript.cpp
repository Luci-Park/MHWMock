#include "pch.h"
#include "CMainPlayerScript.h"
#include "Engine\CCollider3D.h"

CMainPlayerScript::CMainPlayerScript()
	:CScript((UINT)SCRIPT_TYPE::MAINPLAYERSCRIPT)
{
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
}

void CMainPlayerScript::OnCollisionEnter(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER_TYPE::Ground)
	{
		CCollider3D * coll = (CCollider3D*)GetOwner()->GetComponent(COMPONENT_TYPE::COLLIDER3D);
		coll->SetGravity(false);
	}
}

void CMainPlayerScript::SaveToLevelFile(FILE* _File)
{
}

void CMainPlayerScript::LoadFromLevelFile(FILE* _FILE)
{
}
