#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region Wp_Guard
//-------------------------------------------------------------------------------------
//
//									WP_GUARD
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_GUARD::ST_PLAYER_WP_GUARD()
{
}
ST_PLAYER_WP_GUARD::~ST_PLAYER_WP_GUARD()
{
}
void ST_PLAYER_WP_GUARD::Enter(CGameObject* player, PlayerStateMachine* StateMachine) 
{
	StateMachine->ChangeState(L"Wp_Guard_On");
}
void ST_PLAYER_WP_GUARD::Tick(CGameObject* player, PlayerStateMachine* StateMachine) 
{
}
void ST_PLAYER_WP_GUARD::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

//-------------------------------------------------------------------------------------
//
//									WP_GUARD_ON
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_GUARD_ON::ST_PLAYER_WP_GUARD_ON()
{
}
ST_PLAYER_WP_GUARD_ON::~ST_PLAYER_WP_GUARD_ON()
{
}
void ST_PLAYER_WP_GUARD_ON::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_GUARD_ON::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		if(StateMachine->GetASTMParam(L"IsGuard").BOOL)
			StateMachine->ChangeState(L"Wp_Guard_Idle");
		else
			StateMachine->ChangeState(L"Wp_Guard_Off");
	}

	if (KEY_RELEASE(KEY::TAB))
		ChangeASTMParam(StateMachine, L"IsGuard", A_FALSE);
	
}
void ST_PLAYER_WP_GUARD_ON::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_GUARD_ON::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Guard_On")
		m_IsAnimationEnd = true;
}


//-------------------------------------------------------------------------------------
//
//									WP_GUARD_IDLE
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_GUARD_IDLE::ST_PLAYER_WP_GUARD_IDLE()
{
}
ST_PLAYER_WP_GUARD_IDLE::~ST_PLAYER_WP_GUARD_IDLE()
{
}
void ST_PLAYER_WP_GUARD_IDLE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_GUARD_IDLE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::TAB))
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"IsGuard", A_FALSE);
		StateMachine->ChangeState(L"Wp_Guard_Off");
	}

	if (KEY_PRESSED(KEY::LBTN))
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
		ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
		StateMachine->ChangeState(L"Wp_SWITCH");
	}
	if (KEY_PRESSED(KEY::RBTN))
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
		ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
		StateMachine->ChangeState(L"Wp_Bottle_Charge");
	}
	
}
void ST_PLAYER_WP_GUARD_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
//-------------------------------------------------------------------------------------
//
//									WP_GUARD_OFF
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_GUARD_OFF::ST_PLAYER_WP_GUARD_OFF()
{
}
ST_PLAYER_WP_GUARD_OFF::~ST_PLAYER_WP_GUARD_OFF()
{
}
void ST_PLAYER_WP_GUARD_OFF::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_GUARD_OFF::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_GUARD_OFF::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_GUARD_OFF::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Guard_Off")
		m_IsAnimationEnd = true;
}
#pragma endregion
