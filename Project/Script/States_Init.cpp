#include "pch.h"
#include "CMainPlayerScript.h"



//-------------------------------------------------------------------------------------
//
//											Idle
//
//-------------------------------------------------------------------------------------
ST_PLAYER_IDLE::ST_PLAYER_IDLE()
{

}
ST_PLAYER_IDLE::~ST_PLAYER_IDLE()
{
}

void ST_PLAYER_IDLE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_IDLE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_PRESSED(KEY::W)||
		KEY_PRESSED(KEY::A)||
		KEY_PRESSED(KEY::S)||
		KEY_PRESSED(KEY::D))
	{
		StateMachine->ChangeState(L"Move");
	}
}
void ST_PLAYER_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"test", (AnimParamUnion)0);
}

//-------------------------------------------------------------------------------------
//
//											MOVE
//
//-------------------------------------------------------------------------------------

ST_PLAYER_MOVE::ST_PLAYER_MOVE()
{

}
ST_PLAYER_MOVE::~ST_PLAYER_MOVE()
{

}

void ST_PLAYER_MOVE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_MOVE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_PRESSED(KEY::W))
	{
		//Move Forward
		StateMachine->ChangeState(L"Move_Forward");
	}
	if (KEY_PRESSED(KEY::A))
	{
		//Move Backward
	}
	if (KEY_PRESSED(KEY::S))
	{
		//Move Left
	}
	if (KEY_PRESSED(KEY::D))
	{
		//Move Right
	}
}
void ST_PLAYER_MOVE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	int a = 0;
}