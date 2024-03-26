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
	//플레이어의 현재 바라보고 있는 방향
	//그 방향을 기준으로 현재 눌린 방향이 맞는지
	// 근데 카메라를 기준으로 또 봐야 할수도?
	//같은 방향이라면 그냥 전진
	//아니면 그에 맞는 행동



	player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	player->Transform()->GetWorldDir(DIR_TYPE::FRONT);

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
	auto Param = StateMachine->GetASTMParam(L"Dir");
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
//									N	MOVE FORWARD
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
		ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
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
	if (KEY_RELEASE(KEY::S))
	{
		//Stop Move
		ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
		StateMachine->ChangeState(L"N_Idle");
	}
}

void ST_PLAYER_N_MOVE_Backward::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region N_MOVE_RIGHT
//-------------------------------------------------------------------------------------
//
//										MOVE RIGHT
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
	if (KEY_RELEASE(KEY::D))
	{
		//Stop Move
		ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
		StateMachine->ChangeState(L"N_Idle");
	}
}

void ST_PLAYER_N_MOVE_Right::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma endregion

#pragma region Wp_Move

#pragma region Wp_Move_State

ST_PLAYER_WP_MOVE::ST_PLAYER_WP_MOVE()
{

}
ST_PLAYER_WP_MOVE::~ST_PLAYER_WP_MOVE()
{

}

void ST_PLAYER_WP_MOVE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	//플레이어의 현재 바라보고 있는 방향
	//그 방향을 기준으로 현재 눌린 방향이 맞는지
	// 근데 카메라를 기준으로 또 봐야 할수도?
	//같은 방향이라면 그냥 전진
	//아니면 그에 맞는 행동



	player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	player->Transform()->GetWorldDir(DIR_TYPE::FRONT);

	if (KEY_PRESSED(KEY::W))			//Move Forward
		ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
	else if (KEY_PRESSED(KEY::A))		//Move Left
		ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
	else if (KEY_PRESSED(KEY::S))		//Move Backward
		ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
	else if (KEY_PRESSED(KEY::D))		//Move Right	
		ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
}
void ST_PLAYER_WP_MOVE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	auto Param = StateMachine->GetASTMParam(L"Dir");
	int Dir = Param.INT;
	switch (Dir)
	{
	case 0:
		StateMachine->ChangeState(L"Wp_Move_Forward");
		break;
	case 1:
		StateMachine->ChangeState(L"Wp_Move_Left");
		break;
	case 2:
		StateMachine->ChangeState(L"Wp_Move_Backward");
		break;
	case 3:
		StateMachine->ChangeState(L"Wp_Move_Right");
		break;
	default:
		break;
	}
}
void ST_PLAYER_WP_MOVE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
#pragma endregion

#pragma region Wp_Move_Forward

ST_PLAYER_WP_MOVE_Forward::ST_PLAYER_WP_MOVE_Forward()
{

}
ST_PLAYER_WP_MOVE_Forward::~ST_PLAYER_WP_MOVE_Forward()
{

}
void ST_PLAYER_WP_MOVE_Forward::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_MOVE_Forward::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::W))
	{
		//Stop
		ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}

void ST_PLAYER_WP_MOVE_Forward::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Wp_Move_Left

ST_PLAYER_WP_MOVE_Left::ST_PLAYER_WP_MOVE_Left()
{

}
ST_PLAYER_WP_MOVE_Left::~ST_PLAYER_WP_MOVE_Left()
{

}
void ST_PLAYER_WP_MOVE_Left::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_MOVE_Left::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A))
	{
		//Stop
		ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}

void ST_PLAYER_WP_MOVE_Left::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Wp_Move_Right

ST_PLAYER_WP_MOVE_Right::ST_PLAYER_WP_MOVE_Right()
{

}
ST_PLAYER_WP_MOVE_Right::~ST_PLAYER_WP_MOVE_Right()
{

}
void ST_PLAYER_WP_MOVE_Right::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_MOVE_Right::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::D))
	{
		//Stop
		ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}

void ST_PLAYER_WP_MOVE_Right::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Wp_Move_Backward

ST_PLAYER_WP_MOVE_Backward::ST_PLAYER_WP_MOVE_Backward()
{

}
ST_PLAYER_WP_MOVE_Backward::~ST_PLAYER_WP_MOVE_Backward()
{

}
void ST_PLAYER_WP_MOVE_Backward::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_MOVE_Backward::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::S))
	{
		//Stop
		ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}

void ST_PLAYER_WP_MOVE_Backward::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma endregion
