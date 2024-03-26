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
		_stateMachine->ChangeASTMParam(L"IsHit", A_TRUE);
		// �ǰݴ����� ��� ���Ͱ� �÷��̾ ������ ������ �Ѱ�����Ѵ�.
		//_stateMachine->ChangeASTMParam(L"Hit_Dir", A_FORWARD);

		if (_stateMachine->GetParam(L"Wp_on").BOOL)
		{
			_stateMachine->ChangeState(L"ST_PLAYER_WP_HIT");
		}
		else
		{
			_stateMachine->ChangeState(L"ST_PLAYER_N_HIT");
		}
	}
}

void CMainPlayerScript::SaveToLevelFile(FILE* _File)
{
}

void CMainPlayerScript::LoadFromLevelFile(FILE* _FILE)
{
	begin();
}
