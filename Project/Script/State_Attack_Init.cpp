#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region Wp_Attack

ST_PLAYER_WP_ATTACK::ST_PLAYER_WP_ATTACK()
{
}
ST_PLAYER_WP_ATTACK::~ST_PLAYER_WP_ATTACK()
{

}
void ST_PLAYER_WP_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetASTMParam(L"Left_Btn").TRIGGER)
	{
		// ComboSlash01 
	}
}
void ST_PLAYER_WP_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma endregion

#pragma region Wp_Axe_Attack

ST_PLAYER_WP_AXE_ATTACK::ST_PLAYER_WP_AXE_ATTACK()
{
}
ST_PLAYER_WP_AXE_ATTACK::~ST_PLAYER_WP_AXE_ATTACK()
{

}
void ST_PLAYER_WP_AXE_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_AXE_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_AXE_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma endregion