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

	if (_IsInput)
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

		if (KEY_TAP(KEY::LBTN))
		{
			SoundPlay(L"sound\\Player\\01(Move_Start).mp3", 0.5f);
			ChangeASTMParam(StateMachine, L"Wp_on", A_TRUE);
			StateMachine->ChangeScriptParam(L"Wp_On", AnimParamType::BOOL, A_TRUE);
			StateMachine->ChangeScriptParam(L"Left_Btn", AnimParamType::TRIGGER, A_TRUE);
			StateMachine->ChangeState(L"Wp_Idle");
		}

		//Rolling
		if (KEY_TAP(KEY::SPACE))
		{
			ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
			StateMachine->ChangeState(L"N_Rolling");
		}
	}
}
void ST_PLAYER_N_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetASTMParam(L"Wp_on").BOOL ==  true)
		SoundPlay(L"sound\\Player\\15(End_Bust).mp3", 0.5f);

	_IsInput = false;
}

void ST_PLAYER_N_IDLE::OnAnimationBegin(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"N_Idle")
	{
		_IsInput = true;
	}
	else
	{
		_IsInput = false;
	}
}
void ST_PLAYER_N_IDLE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_N_IDLE::OnAnimationEndFinished(IAnimationState* _pState, PlayerStateMachine* StateMachine)
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
			SoundPlay(L"sound\\Player\\16(Wp_off).mp3", 0.5f);
			ChangeASTMParam(StateMachine, L"Wp_on", A_FALSE);
		}

		//Wp_Attack
		if (KEY_TAP(KEY::LBTN))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				StateMachine->ChangeState(L"Wp_Attack");
			}
			else if (KEY_TAP(KEY::TAB))
			{
				ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
				StateMachine->ChangeState(L"Wp_SWITCH");
				return;
			}
			else
			{
				ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
				StateMachine->ChangeState(L"Wp_Attack");
			}
		}
		else if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::LBTN))
			{
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				StateMachine->ChangeState(L"Wp_Attack");
			}
		}
		else if (KEY_PRESSED(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
			StateMachine->ChangeState(L"Wp_Charge");
		}
		if (KEY_TAP(KEY::TAB))
		{
			if (KEY_TAP(KEY::LBTN))
			{
				ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
				StateMachine->ChangeState(L"Wp_SWITCH");
				return;
			}
		}
		else if (KEY_PRESSED(KEY::TAB))
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

		//Rolling
		if (KEY_TAP(KEY::SPACE))
		{
			ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
			StateMachine->ChangeState(L"Wp_Rolling");
		}
}
void ST_PLAYER_WP_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	_IsInput = false;
}

void ST_PLAYER_WP_IDLE::OnAnimationBegin(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Idle")
	{
		_IsInput = true;
	}
	else
	{
		_IsInput = false;
	}
}
void ST_PLAYER_WP_IDLE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Off")
	{
		SoundPlay(L"sound\\Player\\08(Wp_off_End).mp3", 0.5f);
		StateMachine->ChangeScriptParam(L"Wp_On", AnimParamType::BOOL, A_FALSE);
		StateMachine->ChangeState(L"N_Idle");
	}
}
void ST_PLAYER_WP_IDLE::OnAnimationEndFinished(IAnimationState* _pState, PlayerStateMachine* StateMachine)
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
	if (_IsInput)
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
			StateMachine->ChangeScriptParam(L"Wp_On", AnimParamType::BOOL, A_FALSE);
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
}
void ST_PLAYER_AXE_IDLE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	_IsInput = false;
}

void ST_PLAYER_AXE_IDLE::OnAnimationBegin(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Axe_Idle")
	{
		_IsInput = true;
	}
	else
	{
		_IsInput = false;
	}
}
void ST_PLAYER_AXE_IDLE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_IDLE::OnAnimationEndFinished(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

}

#pragma endregion
