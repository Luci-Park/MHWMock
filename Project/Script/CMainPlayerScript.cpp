#include "pch.h"
#include "CMainPlayerScript.h"
#include "Engine\CAnimator3D.h"
#include "Engine\CCollider3D.h"


CMainPlayerScript::CMainPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::MAINPLAYERSCRIPT)
	, _Gravity(true)
	, _Camera(nullptr)
	, _stateMachine(new PlayerStateMachine(GetOwner()))
	, _bCamera(false)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_Camera, "Main Camera");
}

CMainPlayerScript::~CMainPlayerScript()
{
	delete _stateMachine;
}

void CMainPlayerScript::begin()
{
	_stateMachine->setPlayer(GetOwner());
	_stateMachine->setCamera(_Camera);
	_stateMachine->Begin();
}

void CMainPlayerScript::tick()
{
	_stateMachine->Tick();

	if (_stateMachine->GetParam(L"IsHit").BOOL)
	{
		// ChangeState
	}
	if (_Camera != nullptr && _bCamera == false)
	{
		_stateMachine->setCamera(_Camera);
		_bCamera = true;
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

	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER_TYPE::Monster)
	{
		_stateMachine->ChangeASTMParam(L"IsHit", A_TRUE);
	}
}

void CMainPlayerScript::OnAnimationBegin(IAnimationState* _pState)
{
	_stateMachine->OnAnimationBegin(_pState);
}
void CMainPlayerScript::OnAnimationEndStart(IAnimationState* _pState)
{
	_stateMachine->OnAnimationEndStart(_pState);
}
void CMainPlayerScript::OnAnimationEndFinished(IAnimationState* _pState)
{
	_stateMachine->OnAnimationEndFinished(_pState);
}

void CMainPlayerScript::SaveToLevelFile(FILE* _File)
{
}

void CMainPlayerScript::LoadFromLevelFile(FILE* _FILE)
{
	begin();
}
