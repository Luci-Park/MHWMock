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
	, _Sword(nullptr)
	, _Shield(nullptr)
	, _bCamera(false)
	, _bSword(false)
	, _bShield(false)
	, _State()
	, _Stack(0.0f)
{
	_State.Hp = 100;
	_State.IsHitted = false;
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_Camera, "Main Camera");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_Sword, "Sword");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_Shield, "Sheld");
}

CMainPlayerScript::~CMainPlayerScript()
{
	delete _stateMachine;
}

void CMainPlayerScript::Attacked(int Damage, CGameObject* monster)
{
	if (_State.Hp > 10 && !_State.IsHitted)
	{
		_State.Hp -= Damage;
		Hitted(true, monster);
	}
	if (_State.Hp <= 10)
		_State.Hp = 10;
}

void CMainPlayerScript::begin()
{
	//CCollider3D* coll = (CCollider3D*)GetOwner()->GetComponent(COMPONENT_TYPE::COLLIDER3D);
	//if(coll != nullptr)
	//	coll->SetGravity(true);
	_stateMachine->setPlayer(GetOwner());
	_stateMachine->setCamera(_Camera);
	_stateMachine->Begin();
}

void CMainPlayerScript::update()
{
	_stateMachine->Tick();

	if (_Camera != nullptr && _bCamera == false)
	{
		_stateMachine->setCamera(_Camera);
		_bCamera = true;
	}

	if (_Sword != nullptr && _bSword == false)
	{
		_stateMachine->setSword(_Sword);
		_bSword = true;
	}

	if (_Shield != nullptr && _bShield == false)
	{
		_stateMachine->setShield(_Shield);
		_bShield = true;
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
	//fwrite(&m_fSpeed, sizeof(float), 1, _File);
	//SaveResRef(m_pPlayerTexture.Get(), _File);
	//SaveGameObjectParam(m_pTargetObj, _File);

	SaveGameObjectParam(_Camera, _File);
	SaveGameObjectParam(_Sword, _File);
	SaveGameObjectParam(_Shield, _File);
}

void CMainPlayerScript::LoadFromLevelFile(FILE* _FILE)
{
	LoadGameObjectParam(0, _FILE);
	LoadGameObjectParam(1, _FILE);
	LoadGameObjectParam(2, _FILE);
}

void CMainPlayerScript::Hitted(bool ishit, CGameObject* monster)
{
	_stateMachine->ChangeASTMParam(L"IsHit", A_TRUE);

	Vector3 vMonsterPos = monster->Transform()->GetWorldPos();
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

	if (_stateMachine->GetASTMParam(L"Wp_on").BOOL)
	{
		if (_stateMachine->GetASTMParam(L"IsAxe").BOOL == false)
			_stateMachine->ChangeState(L"Wp_HIT");
		else
			_stateMachine->ChangeState(L"Wp_AXE_HIT");
	}
	else
	{
		_stateMachine->ChangeState(L"N_HIT");
	}
}