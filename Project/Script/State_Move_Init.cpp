#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region N_MOVE

#pragma region N_Move_STATE
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
	if (KEY_PRESSED(KEY::W))			//Move Forward
		ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
	else if (KEY_PRESSED(KEY::A))		//Move Left
		ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
	else if (KEY_PRESSED(KEY::S))		//Move Backward
		ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
	else if (KEY_PRESSED(KEY::D))		//Move Right	
		ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
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
		StateMachine->ChangeState(L"N_Move_Left");
		break;
	case 2:
		StateMachine->ChangeState(L"N_Move_Backward");
		break;
	case 3:
		StateMachine->ChangeState(L"N_Move_Right");
		break;
	default:
		break;
	}
}
void ST_PLAYER_N_MOVE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region N_MOVE_FORWARD
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

}

#pragma endregion

#pragma region N_MVOVE_LEFT
//-------------------------------------------------------------------------------------
//
//										MOVE LEFT
//
//-------------------------------------------------------------------------------------


ST_PLAYER_N_MOVE_LEFT::ST_PLAYER_N_MOVE_LEFT()
{

}

ST_PLAYER_N_MOVE_LEFT::~ST_PLAYER_N_MOVE_LEFT()
{

}

void ST_PLAYER_N_MOVE_LEFT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_MOVE_LEFT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A))
	{
		//Stop Move
		ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
		StateMachine->ChangeState(L"N_Idle");
	}
}

void ST_PLAYER_N_MOVE_LEFT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
#pragma endregion

#pragma region N_MOVE_BACKWARD
//-------------------------------------------------------------------------------------
//
//										MOVE BACKWARD
//
//-------------------------------------------------------------------------------------

ST_PLAYER_N_MOVE_Backward::ST_PLAYER_N_MOVE_Backward()
{

}
ST_PLAYER_N_MOVE_Backward::~ST_PLAYER_N_MOVE_Backward()
{

}

void ST_PLAYER_N_MOVE_Backward::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_MOVE_Backward::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_MOVE_Backward::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region N_MOVE_RIGHT
//-------------------------------------------------------------------------------------
//
//										MOVE BACKWARD
//
//-------------------------------------------------------------------------------------

ST_PLAYER_N_MOVE_Right::ST_PLAYER_N_MOVE_Right()
{

}
ST_PLAYER_N_MOVE_Right::~ST_PLAYER_N_MOVE_Right()
{

}

void ST_PLAYER_N_MOVE_Right::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_MOVE_Right::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_MOVE_Right::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma endregion

