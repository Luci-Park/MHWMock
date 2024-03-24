#include "pch.h"
#include "CMainPlayerScript.h"



//-------------------------------------------------------------------------------------
//
//											Idle
//
//-------------------------------------------------------------------------------------
ST_PLAYER_N_IDLE::ST_PLAYER_N_IDLE()
{

}
ST_PLAYER_N_IDLE::~ST_PLAYER_N_IDLE()
{
}

void ST_PLAYER_N_IDLE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_N_IDLE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_PRESSED(KEY::W)||
		KEY_PRESSED(KEY::A)||
		KEY_PRESSED(KEY::S)||
		KEY_PRESSED(KEY::D))
	{
		ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)true);
		StateMachine->ChangeState(L"N_Move");
	}
}
void ST_PLAYER_N_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}