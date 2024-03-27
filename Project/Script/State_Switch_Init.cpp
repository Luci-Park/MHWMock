#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region Switch_Wp
//-------------------------------------------------------------------------------------
//
//											WP_SWITCH
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_SWITCH::ST_PLAYER_WP_SWITCH()
{

}
ST_PLAYER_WP_SWITCH:: ~ST_PLAYER_WP_SWITCH()
{

}
void ST_PLAYER_WP_SWITCH::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SWITCH::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	bool bIsAxe = StateMachine->GetASTMParam(L"IsAxe").BOOL;
	if (bIsAxe)
	{
		StateMachine->ChangeASTMParam(L"IsAxe", A_FALSE);
		StateMachine->ChangeState(L"Wp_SWITCH_AXE_TO_KNIFE");
	}
	else
	{
		StateMachine->ChangeASTMParam(L"IsAxe", A_TRUE);
		StateMachine->ChangeState(L"Wp_SWITCH_KNIFE_TO_AXE");
	}
}
void ST_PLAYER_WP_SWITCH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
//-------------------------------------------------------------------------------------
//
//											WP_SWITCH_KNIFE_TO_AXE
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE::ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE()
{

}
ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE:: ~ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE()
{

}
void ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
}
void ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	StateMachine->ChangeASTMParam(L"IsAttack", A_FALSE);
}
void ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = true;
}

//-------------------------------------------------------------------------------------
//
//											WP_SWITCH_AXE_TO_KNIFE
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE::ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE()
{

}
ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE:: ~ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE()
{

}
void ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	StateMachine->ChangeASTMParam(L"IsAttack", A_FALSE);
}
void ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = true;
}
#pragma endregion
