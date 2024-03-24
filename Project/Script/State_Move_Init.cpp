
#include "pch.h"
#include "CMainPlayerScript.h"

//-------------------------------------------------------------------------------------
//
//											N_MOVE
//
//-------------------------------------------------------------------------------------

ST_PLAYER_N_MOVE::ST_PLAYER_N_MOVE()
{

}
ST_PLAYER_N_MOVE::~ST_PLAYER_N_MOVE()
{

}

void ST_PLAYER_N_MOVE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_PRESSED(KEY::W))
		ChangeASTMParam(StateMachine, L"Dir", (AnimParamUnion)0);
		//Move Left
	else if (KEY_PRESSED(KEY::A))
		ChangeASTMParam(StateMachine, L"Dir", (AnimParamUnion)1);
		//Move Backward
	else if (KEY_PRESSED(KEY::S))
		ChangeASTMParam(StateMachine, L"Dir", (AnimParamUnion)2);
		//Move Right
	else if (KEY_PRESSED(KEY::D))
		ChangeASTMParam(StateMachine, L"Dir", (AnimParamUnion)3);
}
void ST_PLAYER_N_MOVE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	auto Param = GetParam(L"Dir");
	int Dir = Param.INT;
	switch (Dir)
	{
	case 0:
		StateMachine->ChangeState(L"N_Move_Forward");
		break;
	case 1:
		break;
	default:
		break;
	}
}
void ST_PLAYER_N_MOVE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	int a = 0;
}


//-------------------------------------------------------------------------------------
//
//										MOVE FORWARD
//
//-------------------------------------------------------------------------------------

ST_PLAYER_N_MOVE_FORWARD::ST_PLAYER_N_MOVE_FORWARD()
{

}

ST_PLAYER_N_MOVE_FORWARD::~ST_PLAYER_N_MOVE_FORWARD()
{

}

void ST_PLAYER_N_MOVE_FORWARD::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_N_MOVE_FORWARD::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::W))
	{
		//Move Forward
		ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
		StateMachine->ChangeState(L"N_Idle");
	}
	if (KEY_PRESSED(KEY::A))
	{
		//rotate Left
		Quaternion rot = player->Transform()->GetRelativeRot();
		player->Transform()->GetRelativeEulerRot();
	}
	if (KEY_PRESSED(KEY::S))
	{
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		//Move Right
	}
}
void ST_PLAYER_N_MOVE_FORWARD::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	int a = 0;
}