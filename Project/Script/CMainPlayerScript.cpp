#include "pch.h"
#include "CMainPlayerScript.h"
#include "Engine\CAnimator3D.h"
#include "Engine\CCollider3D.h"

#define PI 3.141592

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

		Vector3 vMonsterPos = _Other->GetOwner()->Transform()->GetWorldPos();
		Vector3 vPlayerPos = GetOwner()->Transform()->GetWorldPos();
		Vector3 vPlayerFront = GetOwner()->Transform()->GetWorldDir(DIR_TYPE::FRONT);

		float fDistanceX = vMonsterPos.x - vPlayerPos.x;
		float fDistanceZ = vMonsterPos.z - vPlayerPos.z;

		float fHitAngle = atan2(fDistanceZ, fDistanceX) * 180.f / PI;
		
		fDistanceX = vPlayerFront.x - vPlayerPos.x;
		fDistanceZ = vPlayerFront.z - vPlayerPos.z;
		float fPlayerFrontAngle = atan2(fDistanceZ, fDistanceX) * 180.f / PI;

		float fFinalHitAngle = fHitAngle - fPlayerFrontAngle;

		if (fFinalHitAngle >= -45.f && fFinalHitAngle < 45.f)
		{
			_stateMachine->ChangeASTMParam(L"Hit_Dir", A_BACKWARD);
		}
		else if (fHitAngle >= 45.f && fHitAngle < 135.f)
		{
			_stateMachine->ChangeASTMParam(L"Hit_Dir", A_RIGHT);
		}
		else if (fHitAngle >= 135.f || fHitAngle < -135.f)
		{
			_stateMachine->ChangeASTMParam(L"Hit_Dir", A_FORWARD);
		}
		else if (fHitAngle >= -135.f && fHitAngle < -45.f)
		{
			_stateMachine->ChangeASTMParam(L"Hit_Dir", A_LEFT);
		}

		if (_stateMachine->GetParam(L"Wp_on").BOOL)
		{
			if(_stateMachine->GetParam(L"IsAxe").BOOL)
				_stateMachine->ChangeState(L"Wp_HIT");
			else
				_stateMachine->ChangeState(L"Wp_AXE_HIT");
		}
		else
		{
			_stateMachine->ChangeState(L"N_HIT");
		}
		
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
