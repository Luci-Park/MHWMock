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
	//Moving
	if (KEY_PRESSED(KEY::W)||
		KEY_PRESSED(KEY::A)||
		KEY_PRESSED(KEY::S)||
		KEY_PRESSED(KEY::D))
	{
		ChangeASTMParam(StateMachine, L"IsMove", A_TRUE);
		StateMachine->ChangeState(L"N_Move");
	}

	if (KEY_PRESSED(KEY::LBTN))
	{
		ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_PRESSED(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
	}
}
void ST_PLAYER_N_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

//-------------------------------------------------------------------------------------
//
//										WP	Idle
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_IDLE::ST_PLAYER_WP_IDLE()
{
}
ST_PLAYER_WP_IDLE::~ST_PLAYER_WP_IDLE()
{
}

void ST_PLAYER_WP_IDLE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_IDLE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	//Moving
	if (KEY_PRESSED(KEY::W) ||
		KEY_PRESSED(KEY::A) ||
		KEY_PRESSED(KEY::S) ||
		KEY_PRESSED(KEY::D))
	{
		ChangeASTMParam(StateMachine, L"IsMove", A_TRUE);
		StateMachine->ChangeState(L"N_Move");
	}

	if (KEY_PRESSED(KEY::LBTN))
	{
		ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
		StateMachine->ChangeState(L"");
	}

	//Rolling
	if (KEY_PRESSED(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
	}
}
void ST_PLAYER_WP_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}