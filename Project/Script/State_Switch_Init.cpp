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
	bool bIsAxe = StateMachine->GetASTMParam(L"IsAxe").BOOL;
	if (bIsAxe)
	{
		SoundPlay(L"sound\\Player\\03(Change_to_sword_1).mp3", 0.3f);
		StateMachine->ChangeScriptParam(L"IsAxe", AnimParamType::BOOL, A_FALSE);
		StateMachine->ChangeScriptParam(L"Switch_Wp", AnimParamType::TRIGGER, A_TRUE);
	}
	else
	{
		SoundPlay(L"sound\\Player\\20(Change_to_axe_1).mp3",0.3f);
		StateMachine->ChangeScriptParam(L"IsAxe", AnimParamType::BOOL, A_TRUE);
		StateMachine->ChangeScriptParam(L"Switch_Wp", AnimParamType::TRIGGER, A_TRUE);
	}
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
}
void ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetStateDuration() > 0.5f && _IsPlayed == false)
	{
		SoundPlay(L"sound\\Player\\25(Change_to_axe_2).mp3", 0.3f);
		_IsPlayed = true;
	}

	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
}
void ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	StateMachine->ChangeASTMParam(L"IsAttack", A_FALSE);
	_IsPlayed = false;
}
void ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Knife_to_Axe")
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
	SoundPlay(L"sound\\Player\\05(Attack).mp3", 0.2f);
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetStateDuration() > 0.5f && _IsPlayed == false)
	{
		SoundPlay(L"sound\\Player\\24(Change_to_Sword_2).mp3", 0.3f);
		
		_IsPlayed = true;
	}

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
	if (_pState->GetName() == L"Wp_Axe_to_Knife")
		m_IsAnimationEnd = true;

	_IsPlayed = false;
}
#pragma endregion
