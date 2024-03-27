#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region Wp_Attack

ST_PLAYER_WP_ATTACK::ST_PLAYER_WP_ATTACK()
{
}
ST_PLAYER_WP_ATTACK::~ST_PLAYER_WP_ATTACK()
{

}
void ST_PLAYER_WP_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);

	if (StateMachine->GetASTMParam(L"L+R_Btn").TRIGGER)
	{
		StateMachine->ChangeState(L"Wp_Dash_Attack");
	}
}
void ST_PLAYER_WP_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetASTMParam(L"Left_Btn").TRIGGER)
	{
		// ComboSlash01 
	}
}
void ST_PLAYER_WP_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma endregion

#pragma region Wp Sheld Attack

ST_PLAYER_WP_SHELD_ATTACK::ST_PLAYER_WP_SHELD_ATTACK()
{

}
ST_PLAYER_WP_SHELD_ATTACK::~ST_PLAYER_WP_SHELD_ATTACK()
{

}
void ST_PLAYER_WP_SHELD_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SHELD_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	double duration = StateMachine->GetStateDuration();
	if (duration > 0.5)
	{
		if (KEY_TAP(KEY::RBTN) && KEY_TAP(KEY::TAB))
		{
			ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
			int bottle = StateMachine->GetASTMParam(L"Bottle").INT;
			if (bottle > 0)
			{
				//bottle Charge S
			}
			else
			{
				//bottle Charge F
			}

		}

		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::LBTN))
			{
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Bust", A_TRUE);
				int bottle = StateMachine->GetASTMParam(L"Bottle").INT;
				if (bottle > 0)
				{
					//bust Attack
				}
				else
				{
					//super Bust Attack
				}
			}
		}
	}

}
void ST_PLAYER_WP_SHELD_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Dash Attack

ST_PLAYER_WP_DASH_ATTACK::ST_PLAYER_WP_DASH_ATTACK()
{
}
ST_PLAYER_WP_DASH_ATTACK::~ST_PLAYER_WP_DASH_ATTACK()
{

}
void ST_PLAYER_WP_DASH_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_DASH_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	double duration = StateMachine->GetStateDuration();
	if (duration > 0.45)
	{
		if (KEY_PRESSED(KEY::RBTN) && KEY_PRESSED(KEY::LBTN))
		{
			ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_Sheld_Attack");
		}
	}
}
void ST_PLAYER_WP_DASH_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma endregion


#pragma region Wp_Axe_Attack

ST_PLAYER_WP_AXE_ATTACK::ST_PLAYER_WP_AXE_ATTACK()
{
}
ST_PLAYER_WP_AXE_ATTACK::~ST_PLAYER_WP_AXE_ATTACK()
{

}
void ST_PLAYER_WP_AXE_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_AXE_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_AXE_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma endregion