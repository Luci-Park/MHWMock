#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region N_HIT

ST_PLAYER_N_HIT::ST_PLAYER_N_HIT()
{

}

ST_PLAYER_N_HIT::~ST_PLAYER_N_HIT()
{

}

void ST_PLAYER_N_HIT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_HIT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_HIT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsHit", A_FALSE);
}

#pragma endregion
