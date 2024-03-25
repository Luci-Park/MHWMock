#include "pch.h"
#include "CMainPlayerScript.h"
#include "Engine\CAnimator3D.h"
#include "Engine\CCollider3D.h"


CMainPlayerScript::CMainPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::MAINPLAYERSCRIPT)
	, _Gravity(true)
	, _stateMachine(new PlayerStateMachine(GetOwner()))
{
}

CMainPlayerScript::~CMainPlayerScript()
{
	delete _stateMachine;
}

void CMainPlayerScript::begin()
{
	_stateMachine->setPlayer(GetOwner());
	_stateMachine->Begin();
}

void CMainPlayerScript::tick()
{
	_stateMachine->Tick();
}

void CMainPlayerScript::OnCollisionEnter(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER_TYPE::Ground && _Gravity == true)
	{
		CCollider3D * coll = (CCollider3D*)GetOwner()->GetComponent(COMPONENT_TYPE::COLLIDER3D);
		coll->SetGravity(false);
		_Gravity = false;
	}

	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER_TYPE::Monster)
	{
		_stateMachine->SetASTMParam(L"IsHit", AnimParamType::BOOL, A_TRUE);
	}
}

void CMainPlayerScript::SaveToLevelFile(FILE* _File)
{
}

void CMainPlayerScript::LoadFromLevelFile(FILE* _FILE)
{
	begin();
}
