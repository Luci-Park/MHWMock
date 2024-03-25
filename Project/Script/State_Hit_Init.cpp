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

ST_PLAYER_N_HIT_F::ST_PLAYER_N_HIT_F()
{

}
ST_PLAYER_N_HIT_F::~ST_PLAYER_N_HIT_F()
{

}
void ST_PLAYER_N_HIT_F::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_N_HIT_F::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_N_HIT_F::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
#pragma endregion
