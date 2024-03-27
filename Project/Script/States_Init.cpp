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
	ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
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

	if (KEY_TAP(KEY::LBTN))
	{
		ChangeASTMParam(StateMachine, L"Wp_on", A_TRUE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
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
		//Move
		StateMachine->ChangeState(L"Wp_Move");
	}

	//Wp_off
	if (KEY_PRESSED(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"Wp_on", A_FALSE);
		StateMachine->ChangeState(L"N_Idle");
	}

	//Wp_Attack
	if (KEY_PRESSED(KEY::LBTN))
	{
		if (KEY_PRESSED(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
		}
		else if (KEY_PRESSED(KEY::TAB))
		{
			ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
			StateMachine->ChangeState(L"Wp_SWITCH");
		}
		else
		{
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
		}
		//Attack State
	}
	else if(KEY_PRESSED(KEY::RBTN))
	{
		if (KEY_PRESSED(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
		}
		else if (KEY_PRESSED(KEY::TAB))
		{
			ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
		}
		else
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
		}
		//Attack State
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
	}
}
void ST_PLAYER_WP_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}