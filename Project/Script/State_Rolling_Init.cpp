#include "pch.h"
#include "CMainPlayerScript.h"
//-------------------------------------------------------------------------------------
//
//											N_ROLLING
//
//-------------------------------------------------------------------------------------
ST_PLAYER_N_ROLLING::ST_PLAYER_N_ROLLING()
{
}
ST_PLAYER_N_ROLLING::~ST_PLAYER_N_ROLLING()
{
}

void ST_PLAYER_N_ROLLING::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_N_ROLLING::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"N_Idle");
	}
}
void ST_PLAYER_N_ROLLING::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_N_ROLLING::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"N_Rolling")
		m_IsAnimationEnd = true;
}

//-------------------------------------------------------------------------------------
//
//											WP_ROLLING
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_ROLLING::ST_PLAYER_WP_ROLLING()
{
}
ST_PLAYER_WP_ROLLING::~ST_PLAYER_WP_ROLLING()
{
}

void ST_PLAYER_WP_ROLLING::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ROLLING::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_ROLLING::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ROLLING::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"wp_Rolling")
		m_IsAnimationEnd = true;
}
//-------------------------------------------------------------------------------------
//
//											WP_AXE_ROLLING
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_AXE_ROLLING::ST_PLAYER_WP_AXE_ROLLING()
{
}
ST_PLAYER_WP_AXE_ROLLING::~ST_PLAYER_WP_AXE_ROLLING()
{
}
void ST_PLAYER_WP_AXE_ROLLING::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_AXE_ROLLING::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
}
void ST_PLAYER_WP_AXE_ROLLING::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_AXE_ROLLING::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_axe_Rolling")
		m_IsAnimationEnd = true;
}