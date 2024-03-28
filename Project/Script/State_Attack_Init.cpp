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
	ChangeASTMParam(StateMachine, L"Dir", A_NONE);

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

#pragma region COMBO SLASH

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
	
	if (dAnimationDuration > 0.7f && dAnimationDuration < 1.f)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				// Wp_Sheld_Attack
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				StateMachine->ChangeState(L"Wp_Sheld_Attack");
				return;
			}
			if (KEY_TAP(KEY::TAB))
			{
				// SwitchAttack
			}
			// ComboSlash02
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"Combo_Stack", A_1);
			StateMachine->ChangeState(L"Wp_Attack_ComboSlash_02");
			return;
		}

		Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
		camFront.y = 0;

		Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		playerFront.y = 0;

		auto dot = camFront.Dot(playerFront);

		auto cross = camFront.Cross(playerFront);

		int dir = CalculateDir(dot, cross.y);

		if (KEY_PRESSED(KEY::W))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack F
				//dir
				//R_Bnt
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}

		}
		if (KEY_PRESSED(KEY::D))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack R
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}
		if (KEY_PRESSED(KEY::A))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack L
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}
		if (KEY_PRESSED(KEY::S))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack B
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}

		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::TAB))
			{
				// BottleCharge
				ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				StateMachine->ChangeState(L"Wp_Bottle_Charge");
				return;
			}
		}
		// Charge
		if (KEY_PRESSED(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
			StateMachine->ChangeState(L"Wp_Charge");
		}

	}
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
		StateMachine->ChangeState(L"Wp_Idle");
	}

}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_01::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_01::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Wp_Combo_Slash_01
	if(_pState->GetName() == L"Wp_Combo_Slash_01")
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
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_02::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	double dAnimationDuration = StateMachine->GetStateDuration();

	if (dAnimationDuration > 0.7f && dAnimationDuration < 1.f)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				// Wp_Sheld_Attack
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				StateMachine->ChangeState(L"Wp_Sheld_Attack");
				return;
			}
			if (KEY_TAP(KEY::TAB))
			{
				// SwitchAttack
			}
			// ComboSlash02
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"Combo_Stack", A_2);
			StateMachine->ChangeState(L"Wp_Attack_ComboSlash_03");
			return;
		}

		Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
		camFront.y = 0;

		Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		playerFront.y = 0;

		auto dot = camFront.Dot(playerFront);

		auto cross = camFront.Cross(playerFront);

		int dir = CalculateDir(dot, cross.y);

		if (KEY_PRESSED(KEY::W))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack F
				//dir
				//R_Bnt
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}

		}
		if (KEY_PRESSED(KEY::D))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack R
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}
		if (KEY_PRESSED(KEY::A))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack L
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}
		if (KEY_PRESSED(KEY::S))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack B
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}

		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::TAB))
			{
				// BottleCharge
				ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				StateMachine->ChangeState(L"Wp_Bottle_Charge");
				return;
			}

		}
		// Charge
		if (KEY_PRESSED(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
			StateMachine->ChangeState(L"Wp_Charge");
		}

	}
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_02::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_02::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Wp_Combo_Slash_02
	if (_pState->GetName() == L"Wp_Combo_Slash_02")
		m_IsAnimationEnd = true;
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
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	double dAnimationDuration = StateMachine->GetStateDuration();

	if (dAnimationDuration > 0.7f && dAnimationDuration < 1.f)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				// Wp_Sheld_Attack
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				StateMachine->ChangeState(L"Wp_Sheld_Attack");
				return;
			}
			if (KEY_TAP(KEY::TAB))
			{
				// SwitchAttack
			}
		}

		Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
		camFront.y = 0;

		Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		playerFront.y = 0;

		auto dot = camFront.Dot(playerFront);

		auto cross = camFront.Cross(playerFront);

		int dir = CalculateDir(dot, cross.y);

		if (KEY_PRESSED(KEY::W))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack F
				//dir
				//R_Bnt
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}

		}
		if (KEY_PRESSED(KEY::D))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack R
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}
		if (KEY_PRESSED(KEY::A))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack L
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}
		if (KEY_PRESSED(KEY::S))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack B
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				return;
			}
		}

		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::TAB))
			{
				// BottleCharge
				ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
				StateMachine->ChangeState(L"Wp_Bottle_Charge");
				return;
			}
		}
		
		// Charge
		if (KEY_PRESSED(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
			StateMachine->ChangeState(L"Wp_Charge");
		}
	}
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Wp_Combo_Slash_03
	if (_pState->GetName() == L"Wp_Combo_Slash_03")
		m_IsAnimationEnd = true;
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
	if (duration > 0.4)
	{
		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_PRESSED(KEY::TAB))
			{
				ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
				StateMachine->ChangeState(L"Wp_Bottle_Charge");
			}
		}
		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::LBTN))
			{
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Bust", A_TRUE);
				int bottle = StateMachine->GetASTMParam(L"bottle").INT;
				if (bottle > 0)
				{
					//super Bust Attack
					StateMachine->ChangeState(L"Super_Bust_Attack");
				}
				else
				{
					//bust Attack
					StateMachine->ChangeState(L"Bust_Attack");
				}
			}
		}

		Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
		camFront.y = 0;

		Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		playerFront.y = 0;

		auto dot = camFront.Dot(playerFront);

		auto cross = camFront.Cross(playerFront);
		
		int dir = CalculateDir(dot, cross.y);

		if (KEY_PRESSED(KEY::W))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack F
				//dir
				//R_Bnt
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			}

		}
		if (KEY_PRESSED(KEY::D))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack R
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			}
		}
		if (KEY_PRESSED(KEY::A))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack L
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			}
		}
		if (KEY_PRESSED(KEY::S))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack B
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
			}
		}
	}

	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

}
void ST_PLAYER_WP_SHELD_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SHELD_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Sheld_Attck")
	{
		m_IsAnimationEnd = true;
	}
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

	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	double duration = StateMachine->GetStateDuration();
	if (duration > 0.5)
	{
		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::LBTN))
			{
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				StateMachine->ChangeState(L"Wp_Sheld_Attack");
			}
		}

		if (KEY_TAP(KEY::RBTN ))
		{
			if (KEY_PRESSED(KEY::TAB))
			{
				ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
				StateMachine->ChangeState(L"Wp_Bottle_Charge");
			}
		}

		Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
		camFront.y = 0;

		Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		playerFront.y = 0;

		//�������� ȸ���� ����
		//1 ~ -1
		//0~180�������� ���� ����
		auto dot = camFront.Dot(playerFront);

		//�������� ������ ����
		auto cross = camFront.Cross(playerFront);


		int dir = CalculateDir(dot, cross.y);
		if (KEY_PRESSED(KEY::W))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack F
				//dir
				//R_Bnt
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			}
			
		}
		if (KEY_PRESSED(KEY::D))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack R
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			}
		}
		if (KEY_PRESSED(KEY::A))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack L
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				default:
					break;
				}
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
			}
		}
		if (KEY_PRESSED(KEY::S))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack B
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				switch (dir)
				{
				case A_F:
					ChangeASTMParam(StateMachine, L"Dir", A_0);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_F");
					break;
				case A_L:
					ChangeASTMParam(StateMachine, L"Dir", A_3);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_R");
					break;
				case A_B:
					ChangeASTMParam(StateMachine, L"Dir", A_2);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_B");
					break;
				case A_R:
					ChangeASTMParam(StateMachine, L"Dir", A_1);
					StateMachine->ChangeState(L"Wp_Sliding_Attack_L");
					break;
				default:
					break;
				}
			}
		}
	}

}
void ST_PLAYER_WP_DASH_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_DASH_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Dash_Attack")
	{
		m_IsAnimationEnd = true;
	}
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
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	double duration = StateMachine->GetStateDuration();
	if (duration > 0.5f)
	{
		if (KEY_PRESSED(KEY::LBTN))
		{
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
			StateMachine->ChangeState(L"Wp_Charge_K_Enchent");
		}
	}
}
void ST_PLAYER_WP_BOTTLE_CHARGE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_BOTTLE_CHARGE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"wp_Bottle_Charge_S")
	{
		m_IsAnimationEnd = true;
	}
	if (_pState->GetName() == L"wp_Bottle_Charge_F")
	{
		m_IsAnimationEnd = true;
	}

}

#pragma endregion

#pragma region Wp_Enchent Knife

ST_PLAYER_WP_CHARGE_K_ENCHENT::ST_PLAYER_WP_CHARGE_K_ENCHENT()
{

}
ST_PLAYER_WP_CHARGE_K_ENCHENT::~ST_PLAYER_WP_CHARGE_K_ENCHENT()
{

}

void ST_PLAYER_WP_CHARGE_K_ENCHENT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_CHARGE_K_ENCHENT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_PRESSED(KEY::LBTN))
	{
		float overload = StateMachine->GetASTMParam(L"OverLoad").FLOAT;
		overload += 2 * CTimeMgr::GetInst()->GetDeltaTime();
		ChangeASTMParam(StateMachine,L"OverLoad", (AnimParamUnion)overload);
	}
	if (KEY_RELEASE(KEY::LBTN))
	{
		float overload = StateMachine->GetASTMParam(L"OverLoad").FLOAT;
		ChangeASTMParam(StateMachine, L"IsHolding", A_FALSE);
		if (overload > 2)
			StateMachine->ChangeState(L"Wp_K_Enchent_Attack");
		else
			StateMachine->ChangeState(L"Wp_Upper_Slash");
	}
}
void ST_PLAYER_WP_CHARGE_K_ENCHENT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_CHARGE_K_ENCHENT::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Wp_Charge_Enchent_Knife
}

#pragma endregion

#pragma region Wp Enchent K Attack

ST_PLAYER_WP_K_ENCHENT_ATTACK::ST_PLAYER_WP_K_ENCHENT_ATTACK()
{

}
ST_PLAYER_WP_K_ENCHENT_ATTACK::~ST_PLAYER_WP_K_ENCHENT_ATTACK()
{

}

void ST_PLAYER_WP_K_ENCHENT_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	//enchent k
}
void ST_PLAYER_WP_K_ENCHENT_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_K_ENCHENT_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"OverLoad", (AnimParamUnion)0.f);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_K_ENCHENT_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//wp_Enchent_K_Attack
	if (_pState->GetName() == L"wp_Enchent_K_Attack")
		m_IsAnimationEnd = true;
}

#pragma endregion



#pragma region WP Charge
//-------------------------------------------------------------------------------------
//
//										wp_Charge
//
//-------------------------------------------------------------------------------------

ST_PLAYER_WP_CHARGE::ST_PLAYER_WP_CHARGE()
{

}
ST_PLAYER_WP_CHARGE::~ST_PLAYER_WP_CHARGE()
{

}

void ST_PLAYER_WP_CHARGE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_CHARGE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::RBTN))
	{
		double dAnimationDuration = StateMachine->GetStateDuration();

		if (dAnimationDuration < 0.5f)
		{
			// UPPER SLASH
			ChangeASTMParam(StateMachine, L"Stack", A_1);
			ChangeASTMParam(StateMachine, L"IsHolding", A_FALSE);
			StateMachine->ChangeState(L"Wp_Upper_Slash");
		}
		else
		{
			// DOUBLE SLASH
			ChangeASTMParam(StateMachine, L"Stack", A_2);
			ChangeASTMParam(StateMachine, L"IsHolding", A_FALSE);
			StateMachine->ChangeState(L"Wp_Double_Slash");
		}
	}

}
void ST_PLAYER_WP_CHARGE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_CHARGE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

}
#pragma endregion

#pragma region Double Slash

//-------------------------------------------------------------------------------------
//
//										wp_Double_Slash
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_DOUBLE_SLASH::ST_PLAYER_WP_DOUBLE_SLASH()
{

}
ST_PLAYER_WP_DOUBLE_SLASH::~ST_PLAYER_WP_DOUBLE_SLASH()
{

}

void ST_PLAYER_WP_DOUBLE_SLASH::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_DOUBLE_SLASH::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"OverLoad", (AnimParamUnion)0.f);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_DOUBLE_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_DOUBLE_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//wp_Double_Slash
	if (_pState->GetName() == L"wp_Upper_Slash")
		m_IsAnimationEnd = true;
}

#pragma endregion

#pragma region Upper Slash

//-------------------------------------------------------------------------------------
//
//										wp_Upper_Slash
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_UPPER_SLASH::ST_PLAYER_WP_UPPER_SLASH()
{

}
ST_PLAYER_WP_UPPER_SLASH::~ST_PLAYER_WP_UPPER_SLASH()
{

}

void ST_PLAYER_WP_UPPER_SLASH::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_UPPER_SLASH::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"OverLoad", (AnimParamUnion)0.f);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_UPPER_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_UPPER_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//wp_Upper_Slash
	if (_pState->GetName() == L"wp_Upper_Slash")
		m_IsAnimationEnd = true;
}

#pragma endregion

#pragma region Sliding Attack F

ST_PLAYER_WP_SLIDING_ATTACK_F::ST_PLAYER_WP_SLIDING_ATTACK_F()
{

}
ST_PLAYER_WP_SLIDING_ATTACK_F::~ST_PLAYER_WP_SLIDING_ATTACK_F()
{

}

void ST_PLAYER_WP_SLIDING_ATTACK_F::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_F::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_SLIDING_ATTACK_F::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_F::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_Sliding_Attack_Forward")
	{
		m_IsAnimationEnd = true;
	}
}

#pragma endregion

#pragma region Sliding Attack L

ST_PLAYER_WP_SLIDING_ATTACK_L::ST_PLAYER_WP_SLIDING_ATTACK_L()
{

}
ST_PLAYER_WP_SLIDING_ATTACK_L::~ST_PLAYER_WP_SLIDING_ATTACK_L()
{

}

void ST_PLAYER_WP_SLIDING_ATTACK_L::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_L::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_SLIDING_ATTACK_L::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_L::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	
	if (_pState->GetName() == L"Wp_Sliding_Attack_Left")
	{
		m_IsAnimationEnd = true;
	}
}

#pragma endregion

#pragma region Sliding Attack B

ST_PLAYER_WP_SLIDING_ATTACK_B::ST_PLAYER_WP_SLIDING_ATTACK_B()
{

}
ST_PLAYER_WP_SLIDING_ATTACK_B::~ST_PLAYER_WP_SLIDING_ATTACK_B()
{

}

void ST_PLAYER_WP_SLIDING_ATTACK_B::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_B::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_B::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_SLIDING_ATTACK_B::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"wp_Sliding_Attack_Backward")
	{
		m_IsAnimationEnd = true;
	}
}

#pragma endregion

#pragma region Sliding Attack R

ST_PLAYER_WP_SLIDING_ATTACK_R::ST_PLAYER_WP_SLIDING_ATTACK_R()
{

}
ST_PLAYER_WP_SLIDING_ATTACK_R::~ST_PLAYER_WP_SLIDING_ATTACK_R()
{

}

void ST_PLAYER_WP_SLIDING_ATTACK_R::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_R::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_SLIDING_ATTACK_R::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_R::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"wp_Sliding_Attack_Right")
	{
		m_IsAnimationEnd = true;
	}
}

#pragma endregion

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

#pragma region SuperBust Attack
ST_PLAYER_SUPER_BUST_ATTACK::ST_PLAYER_SUPER_BUST_ATTACK()
{

}
ST_PLAYER_SUPER_BUST_ATTACK::~ST_PLAYER_SUPER_BUST_ATTACK()
{

}

void ST_PLAYER_SUPER_BUST_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_SUPER_BUST_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_SUPER_BUST_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_SUPER_BUST_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Super_Bust_Attack
	//Super_Bust_Attack_End
	if (_pState->GetName() == L"bust_Attack_End")
	{
		ChangeASTMParam(StateMachine, L"Bust", A_FALSE);
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"IsAxe", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
#pragma endregion

#pragma region Bust Attack

ST_PLAYER_BUST_ATTACK::ST_PLAYER_BUST_ATTACK()
{

}
ST_PLAYER_BUST_ATTACK::~ST_PLAYER_BUST_ATTACK()
{

}

void ST_PLAYER_BUST_ATTACK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_BUST_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_BUST_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_BUST_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//bust_Attack
	if (_pState->GetName() == L"bust_Attack")
		m_IsAnimationEnd = true;

	if (_pState->GetName() == L"bust_Attack_End")
	{
		ChangeASTMParam(StateMachine, L"Bust", A_FALSE);
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"IsAxe", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}

#pragma endregion

