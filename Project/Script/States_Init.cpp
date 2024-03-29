#include "pch.h"
#include "CMainPlayerScript.h"


#pragma region N Idle


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
		StateMachine->ChangeState(L"N_Rolling");
	}
}
void ST_PLAYER_N_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma endregion

#pragma region Wp Idle



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
	ChangeASTMParam(StateMachine, L"IsGuard", A_FALSE);
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
	if (KEY_TAP(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"Wp_on", A_FALSE);
		StateMachine->ChangeState(L"N_Idle");
	}

	//Wp_Attack
	if (KEY_TAP(KEY::LBTN))
	{
		if (KEY_TAP(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_Attack");
		}
		else if (KEY_PRESSED(KEY::TAB))
		{
			ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
			StateMachine->ChangeState(L"Wp_SWITCH");
		}
		else
		{
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_Attack");
		}
	}
	else if(KEY_TAP(KEY::RBTN))
	{
		if (KEY_TAP(KEY::LBTN))
		{
			ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_Attack");
		}
	}

	if (KEY_PRESSED(KEY::TAB))
	{
		if (KEY_TAP(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_Bottle_Charge");
			return;
		}

		ChangeASTMParam(StateMachine, L"IsGuard", A_TRUE);
		StateMachine->ChangeState(L"Wp_Guard");
		return;
	}

	if (KEY_PRESSED(KEY::RBTN))
	{
		ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
		ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
		ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
		StateMachine->ChangeState(L"Wp_Charge");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"Wp_Rolling");
	}
}
void ST_PLAYER_WP_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma endregion

#pragma region Wp Axe Idle

ST_PLAYER_AXE_IDLE::ST_PLAYER_AXE_IDLE()
{
}
ST_PLAYER_AXE_IDLE::~ST_PLAYER_AXE_IDLE()
{
}

void ST_PLAYER_AXE_IDLE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_AXE_IDLE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	//Moving
	if (KEY_PRESSED(KEY::W) ||
		KEY_PRESSED(KEY::A) ||
		KEY_PRESSED(KEY::S) ||
		KEY_PRESSED(KEY::D))
	{
		ChangeASTMParam(StateMachine, L"IsMove", A_TRUE);
		//Move
		StateMachine->ChangeState(L"Wp_AXE_Move");
		return;
	}

	//Wp_off
	if (KEY_TAP(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsAxe", A_FALSE);
		ChangeASTMParam(StateMachine, L"Wp_on", A_FALSE);
		StateMachine->ChangeState(L"N_Idle");
		return;
	}

	//Wp_Attack
	if (KEY_TAP(KEY::LBTN))
	{
		if (KEY_TAP(KEY::RBTN))
		{
			//ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
		}
		else if (KEY_PRESSED(KEY::TAB))
		{
			ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
			StateMachine->ChangeState(L"Wp_SWITCH");
			return;
		}
		else
		{
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_AXE_Attack");
			return;
		}
	}
	else if (KEY_TAP(KEY::RBTN))
	{
		if (KEY_TAP(KEY::LBTN))
		{
			//ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
		}
		else if (KEY_TAP(KEY::TAB))
		{
			//ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
		}
		else
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_AXE_Attack");
			return;
		}
		//Attack State
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"Wp_AXE_Rolling");
	}
}
void ST_PLAYER_AXE_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion
