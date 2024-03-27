#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region Wp_Attack
//-------------------------------------------------------------------------------------
//
//											Wp_ATTACK
//
//-------------------------------------------------------------------------------------
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

	if (StateMachine->GetASTMParam(L"Left_Btn").TRIGGER)
	{
		StateMachine->ChangeState(L"Wp_Attack_ComboSlash_01");
	}
}
void ST_PLAYER_WP_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	
}
void ST_PLAYER_WP_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
//-------------------------------------------------------------------------------------
//
//											WP_ATTACK_COMBOSLASH_01
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_ATTACK_COMBOSLASH_01::ST_PLAYER_WP_ATTACK_COMBOSLASH_01()
{
}
ST_PLAYER_WP_ATTACK_COMBOSLASH_01::~ST_PLAYER_WP_ATTACK_COMBOSLASH_01()
{

}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_01::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_01::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	double dAnimationDuration = StateMachine->GetStateDuration();
	
	if (dAnimationDuration > 0.8f && dAnimationDuration < 1.f)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				// 방패찌르기
				int a = 0;
			}
			if (KEY_TAP(KEY::TAB))
			{
				// 변형베기
				int a = 0;
			}
			// 콤보 2
			ChangeASTMParam(StateMachine, L"Combo_Stack", A_1);
			int a = 0;
		}

		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::TAB))
			{
				// 병차지 S & F
				int a = 0;
			}
			if (KEY_TAP(KEY::W))
			{
				// 슬라이딩 어택
				int a = 0;
			}
			if (KEY_TAP(KEY::A))
			{
				// 슬라이딩 어택
				int a = 0;
			}
			if (KEY_TAP(KEY::S))
			{
				// 슬라이딩 어택
				int a = 0;
			}
			if (KEY_TAP(KEY::D))
			{
				// 슬라이딩 어택
				int a = 0;
			}
			// 차지
			int a = 0;
		}

	}
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_01::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_01::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = true;
}

//-------------------------------------------------------------------------------------
//
//											WP_ATTACK_COMBOSLASH_02
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_ATTACK_COMBOSLASH_02::ST_PLAYER_WP_ATTACK_COMBOSLASH_02()
{
}
ST_PLAYER_WP_ATTACK_COMBOSLASH_02::~ST_PLAYER_WP_ATTACK_COMBOSLASH_02()
{

}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_02::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_02::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_02::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_02::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

}
//-------------------------------------------------------------------------------------
//
//											WP_ATTACK_COMBOSLASH_03
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_ATTACK_COMBOSLASH_03::ST_PLAYER_WP_ATTACK_COMBOSLASH_03()
{
}
ST_PLAYER_WP_ATTACK_COMBOSLASH_03::~ST_PLAYER_WP_ATTACK_COMBOSLASH_03()
{

}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
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
			StateMachine->ChangeState(L"Wp_Bottle_Charge");
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
void ST_PLAYER_WP_SHELD_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
	StateMachine->ChangeState(L"Wp_Idle");
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
		if (KEY_TAP(KEY::RBTN) && KEY_TAP(KEY::LBTN))
		{
			ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_Sheld_Attack");
		}

		if (KEY_TAP(KEY::RBTN) && KEY_TAP(KEY::TAB))
		{
			ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_Bottle_Charge");
		}
	}
}
void ST_PLAYER_WP_DASH_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_DASH_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
	StateMachine->ChangeState(L"Wp_Idle");
}
#pragma endregion

#pragma region BottleCharge

ST_PLAYER_WP_BOTTLE_CHARGE::ST_PLAYER_WP_BOTTLE_CHARGE()
{

}
ST_PLAYER_WP_BOTTLE_CHARGE::~ST_PLAYER_WP_BOTTLE_CHARGE()
{

}
void ST_PLAYER_WP_BOTTLE_CHARGE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_BOTTLE_CHARGE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_BOTTLE_CHARGE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_BOTTLE_CHARGE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
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