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
		SoundPlay(L"sound\\Player\\04(Big_Attack).mp3",0.2f);
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
	SoundPlay(L"sound\\Player\\05(Attack).mp3",0.2f);
}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_01::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_Rolling");
	}

	double dAnimationDuration = StateMachine->GetStateDuration();
	
	if (dAnimationDuration > 0.5f && dAnimationDuration < 1.f)
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
				ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
				StateMachine->ChangeState(L"Wp_SWITCH");
			}
			// ComboSlash02
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"Combo_Stack", A_1);
			SoundPlay(L"sound\\Player\\10(Attack_2).mp3", 0.2f);
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
		
		if (KEY_PRESSED(KEY::TAB))
		{
			if (KEY_TAP(KEY::RBTN))
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
			if (KEY_PRESSED(KEY::W) ||
				KEY_PRESSED(KEY::A) ||
				KEY_PRESSED(KEY::S) ||
				KEY_PRESSED(KEY::D))
			{

			}
			else
			{
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
				StateMachine->ChangeState(L"Wp_Charge");
			}
		}

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
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_Rolling");
	}

	double dAnimationDuration = StateMachine->GetStateDuration();

	if (dAnimationDuration > 0.5f && dAnimationDuration < 1.f)
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
				ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
				StateMachine->ChangeState(L"Wp_SWITCH");
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

		if (KEY_PRESSED(KEY::TAB))
		{
			if (KEY_TAP(KEY::RBTN))
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
			if (KEY_PRESSED(KEY::W) ||
				KEY_PRESSED(KEY::A) ||
				KEY_PRESSED(KEY::S) ||
				KEY_PRESSED(KEY::D))
			{

			}
			else
			{
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
				StateMachine->ChangeState(L"Wp_Charge");
			}
		}

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
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"Combo_Stack", A_0);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_Rolling");
	}

	double dAnimationDuration = StateMachine->GetStateDuration();

	if (dAnimationDuration > 0.2f && _IsPlayed == false)
	{
		SoundPlay(L"sound\\Player\\04(Big_Attack).mp3", 0.2f);
		_IsPlayed = true;
	}

	if (dAnimationDuration > 0.5f && dAnimationDuration < 1.f)
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
				ChangeASTMParam(StateMachine, L"Switch_wp", A_TRUE);
				StateMachine->ChangeState(L"Wp_SWITCH");
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

		if (KEY_PRESSED(KEY::TAB))
		{
			if (KEY_TAP(KEY::RBTN))
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
			if (KEY_PRESSED(KEY::W)||
				KEY_PRESSED(KEY::A)||
				KEY_PRESSED(KEY::S)||
				KEY_PRESSED(KEY::D))
			{

			}
			else
			{
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"IsAttack", A_TRUE);
				ChangeASTMParam(StateMachine, L"IsHolding", A_TRUE);
				StateMachine->ChangeState(L"Wp_Charge");
			}
		}
	}

}
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	_IsPlayed = false;
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
	StateMachine->ChangeScriptParam(L"Shield_Attack", AnimParamType::TRIGGER, A_TRUE);
	SoundPlay(L"sound\\Player\\32(Sheld_Attack,bottle).mp3");
}
void ST_PLAYER_WP_SHELD_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_Rolling");
	}

	double duration = StateMachine->GetStateDuration();
	if (duration > 0.4)
	{
		if (KEY_PRESSED(KEY::TAB))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				// BottleCharge
				ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
				StateMachine->ChangeState(L"Wp_Bottle_Charge");
				return;
			}
		}
		if (KEY_TAP(KEY::RBTN))
		{
			if (KEY_TAP(KEY::LBTN))
			{
				ChangeASTMParam(StateMachine, L"L+R_Btn", A_TRUE);
				ChangeASTMParam(StateMachine, L"Bust", A_TRUE);
				
				//super Bust Attack
				StateMachine->ChangeState(L"Bust_Attack_Axe_Link");
			
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

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_Rolling");
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

		if (KEY_PRESSED(KEY::TAB))
		{
			if (KEY_TAP(KEY::RBTN))
			{
				// BottleCharge
				ChangeASTMParam(StateMachine, L"R+S_Btn", A_TRUE);
				StateMachine->ChangeState(L"Wp_Bottle_Charge");
				return;
			}
		}

		if (nullptr == StateMachine->GetCamera())
			return;

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
	float overload = StateMachine->GetASTMParam(L"OverLoad").FLOAT;
	StateMachine->ChangeScriptParam(L"Bottle_Charge",AnimParamType::TRIGGER,A_TRUE);
	AnimParamUnion tmp;
	tmp.FLOAT = overload;
	StateMachine->ChangeScriptParam(L"OverLoad", AnimParamType::FLOAT, tmp);
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
			StateMachine->ChangeScriptParam(L"Left_Btn", AnimParamType::TRIGGER, A_TRUE);
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
	//if (KEY_PRESSED(KEY::LBTN))
	//{
	//	float overload = StateMachine->GetASTMParam(L"OverLoad").FLOAT;
	//	overload += 2 * CTimeMgr::GetInst()->GetDeltaTime();
	//	ChangeASTMParam(StateMachine,L"OverLoad", (AnimParamUnion)overload);
	//}
	double duration = StateMachine->GetStateDuration();
	if (KEY_RELEASE(KEY::LBTN))
	{
		if (duration < 0.5)
		{
			ChangeASTMParam(StateMachine, L"Stack", A_0);
			ChangeASTMParam(StateMachine, L"IsHolding", A_FALSE);
			StateMachine->ChangeState(L"Wp_Upper_Slash");
		}
		else
		{
			ChangeASTMParam(StateMachine, L"Stack", A_1);
			ChangeASTMParam(StateMachine, L"IsHolding", A_FALSE);
			StateMachine->ChangeState(L"Wp_K_Enchent_Attack");
		}
	}
}
void ST_PLAYER_WP_CHARGE_K_ENCHENT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_CHARGE_K_ENCHENT::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Wp_Charge_Enchent_Knife
	//if (_pState->GetName() == L"Wp_Charge_Enchent_Knife")
	//{
	//	ChangeASTMParam(StateMachine, L"Stack", A_1);
	//	ChangeASTMParam(StateMachine, L"IsHolding", A_FALSE);
	//	StateMachine->ChangeState(L"Wp_K_Enchent_Attack");
	//}
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
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"OverLoad", (AnimParamUnion)0.f);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_Rolling");
	}

}
void ST_PLAYER_WP_K_ENCHENT_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

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
	double dAnimationDuration = StateMachine->GetStateDuration();

	if (KEY_RELEASE(KEY::RBTN))
	{

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

	if (dAnimationDuration > 0.5f && !_IsPlayed)
	{
		SoundPlay(L"sound\\Player\\43(Charge_S).mp3",0.5);
		_IsPlayed = true;
	}

}
void ST_PLAYER_WP_CHARGE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	_IsPlayed = false;
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
		ChangeASTMParam(StateMachine, L"Stack", (AnimParamUnion)0.f);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Rolling");
	}

}
void ST_PLAYER_WP_DOUBLE_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_DOUBLE_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//wp_Double_Slash
	if (_pState->GetName() == L"wp_Double_Slash")
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
		ChangeASTMParam(StateMachine, L"Stack", (AnimParamUnion)0.f);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_Rolling");
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
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_SLIDING_ATTACK_B::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

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
	ChangeASTMParam(StateMachine,L"IsAttack", A_TRUE);

	if (StateMachine->GetASTMParam(L"Left_Btn").TRIGGER)
	{
		StateMachine->ChangeState(L"Wp_AXE_Upper_Slash");
	}

	if (StateMachine->GetASTMParam(L"Right_Btn").TRIGGER)
	{
		StateMachine->ChangeState(L"Wp_AXE_Horizontal_Slash");
	}
}
void ST_PLAYER_WP_AXE_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_AXE_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma region Wp_axe_Upper_Slash

ST_PLAYER_AXE_UPPER_SLASH::ST_PLAYER_AXE_UPPER_SLASH()
{

}
ST_PLAYER_AXE_UPPER_SLASH::~ST_PLAYER_AXE_UPPER_SLASH()
{

}

void ST_PLAYER_AXE_UPPER_SLASH::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_UPPER_SLASH::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}

	double duration = StateMachine->GetStateDuration();
	if (duration > 0.5)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_AXE_Down_Slash");
		}

		else if (KEY_TAP(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_AXE_Horizontal_Slash");
		}

		//Rolling
		if (KEY_TAP(KEY::SPACE))
		{
			StateMachine->ChangeState(L"Wp_AXE_Rolling");
		}
	}
}
void ST_PLAYER_AXE_UPPER_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_UPPER_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if ((_pState->GetName() == L"Wp_axe_upper_Slash" && !StateMachine->GetASTMParam(L"Left_Btn").BOOL)
		|| (_pState->GetName() == L"Wp_axe_upper_Slash" && !StateMachine->GetASTMParam(L"Right_Btn").BOOL))
	{
		m_IsAnimationEnd = true;
	}


}

#pragma endregion

#pragma region Wp_axe_Down_Slash

ST_PLAYER_AXE_DOWN_SLASH::ST_PLAYER_AXE_DOWN_SLASH()
{

}
ST_PLAYER_AXE_DOWN_SLASH::~ST_PLAYER_AXE_DOWN_SLASH()
{

}

void ST_PLAYER_AXE_DOWN_SLASH::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_DOWN_SLASH::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		if (!StateMachine->GetASTMParam(L"Left_Btn").BOOL
			|| !StateMachine->GetASTMParam(L"Right_Btn").BOOL)
		{
			ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
			StateMachine->ChangeState(L"Wp_AXE_Idle");
			return;
		}
		
		return;
	}

	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_AXE_Rolling");
	}

	double duration = StateMachine->GetStateDuration();
	if (duration > 0.5)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			ChangeASTMParam(StateMachine, L"Left_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_AXE_Down_to_Up_Link");
			return;
		}
		else if (KEY_TAP(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_AXE_Horizontal_Slash");
			return;
		}
	}

}
void ST_PLAYER_AXE_DOWN_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_DOWN_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Wp_axe_down_Slash
	if ((_pState->GetName() == L"Wp_axe_down_Slash" && !StateMachine->GetASTMParam(L"Left_Btn").BOOL)
		|| (_pState->GetName() == L"Wp_axe_down_Slash" && !StateMachine->GetASTMParam(L"Right_Btn").BOOL))
	{
		m_IsAnimationEnd = true;
	}
	
}

#pragma endregion

#pragma region WP_AXE_DOWN_TO_UP

ST_PLAYER_AXE_DOWN_To_UP::ST_PLAYER_AXE_DOWN_To_UP()
{

}
ST_PLAYER_AXE_DOWN_To_UP::~ST_PLAYER_AXE_DOWN_To_UP()
{

}

void ST_PLAYER_AXE_DOWN_To_UP::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_DOWN_To_UP::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_DOWN_To_UP::Exit(CGameObject* player, PlayerStateMachine* StateMachine) 
{

}
void ST_PLAYER_AXE_DOWN_To_UP::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_axe_Down_to_Up")
	{
		StateMachine->ChangeState(L"Wp_AXE_Upper_Slash");
	}
}

#pragma endregion


#pragma region Wp_axe_Horizontal_Slash

ST_PLAYER_AXE_HORIZONTAL_SLASH::ST_PLAYER_AXE_HORIZONTAL_SLASH()
{

}
ST_PLAYER_AXE_HORIZONTAL_SLASH::~ST_PLAYER_AXE_HORIZONTAL_SLASH()
{

}

void ST_PLAYER_AXE_HORIZONTAL_SLASH::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_HORIZONTAL_SLASH::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_AXE_Rolling");
	}
	double duration = StateMachine->GetStateDuration();

	if (duration > 0.5)
	{
		if (KEY_TAP(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			StateMachine->ChangeState(L"Wp_AXE_Turnning_Slash");
			return;
		}

	
	}

}
void ST_PLAYER_AXE_HORIZONTAL_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_HORIZONTAL_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Wp_axe_Horzontal_Slash
	if (_pState->GetName() == L"Wp_axe_Horzontal_Slash")
	{
		m_IsAnimationEnd = true;
	}
}

#pragma endregion

#pragma region Wp_Axe_Turnning_Slash

ST_PLAYER_AXE_TURNNING_SLASH::ST_PLAYER_AXE_TURNNING_SLASH()
{

}
ST_PLAYER_AXE_TURNNING_SLASH::~ST_PLAYER_AXE_TURNNING_SLASH()
{

}

void ST_PLAYER_AXE_TURNNING_SLASH::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_TURNNING_SLASH::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
	//Rolling
	if (KEY_TAP(KEY::SPACE))
	{
		StateMachine->ChangeState(L"Wp_AXE_Rolling");
	}
	double duration = StateMachine->GetStateDuration();

	if (duration > 0.5)
	{
		if (KEY_TAP(KEY::RBTN))
		{
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			ChangeASTMParam(StateMachine, L"Bust", A_TRUE);
			StateMachine->ChangeState(L"Bust_Attack_Axe_Link");
			return;
		}

		
	}
}
void ST_PLAYER_AXE_TURNNING_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_AXE_TURNNING_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Wp_axe_Turning_Slash
	if (_pState->GetName() == L"Wp_axe_Turning_Slash")
	{
		m_IsAnimationEnd = true;
	}
}

#pragma endregion



#pragma endregion


#pragma region BUST_ATTACK_AXE_LINK
ST_PLAYER_BUST_ATTACK_AXE_LINK::ST_PLAYER_BUST_ATTACK_AXE_LINK()
	: _SubPlayed(false)
{

}
ST_PLAYER_BUST_ATTACK_AXE_LINK::~ST_PLAYER_BUST_ATTACK_AXE_LINK()
{

}

void ST_PLAYER_BUST_ATTACK_AXE_LINK::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	
}
void ST_PLAYER_BUST_ATTACK_AXE_LINK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	int iBottle = StateMachine->GetASTMParam(L"bottle").INT;

	if (StateMachine->GetASTMParam(L"IsAxe").BOOL)
	{
		StateMachine->ChangeScriptParam(L"IsAxe", AnimParamType::BOOL, A_TRUE);
	}

	if (iBottle == 0 && _IsPlayed == false)
	{
		SoundPlay(L"sound\\Player\\10(Merge).mp3");
		_IsPlayed = true;
	}
	else if(iBottle > 0 && _IsPlayed == false)
	{
		SoundPlay(L"sound\\Player\\06(Super_Bust_Attack_Charge).mp3");
		_IsPlayed = true;
	}

	if (StateMachine->GetStateDuration() > 0.5f && _SubPlayed == false && iBottle > 0)
	{
		SoundPlay(L"sound\\Player\\02(Super_Bust_Attack).mp3");
		_SubPlayed = true;
	}
	
	if (m_IsAnimationEnd)
	{
		if (iBottle == 0)
		{
			StateMachine->ChangeScriptParam(L"Bust_Attack", AnimParamType::TRIGGER, A_TRUE);
			StateMachine->ChangeState(L"Bust_Attack");
		}
		else
		{
			StateMachine->ChangeScriptParam(L"Super_Bust_Attack", AnimParamType::TRIGGER, A_TRUE);
			StateMachine->ChangeState(L"Super_Bust_Attack");
		}
	}

}
void ST_PLAYER_BUST_ATTACK_AXE_LINK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	_IsPlayed = false;
	_SubPlayed = false;
}
void ST_PLAYER_BUST_ATTACK_AXE_LINK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetASTMParam(L"IsAxe").BOOL)
	{
		if (_pState->GetName() == L"Bust_Attack_Axe_Link")
		{
			m_IsAnimationEnd = true;
		}
	}
	else
	{
		if (_pState->GetName() == L"Bust_Attack_Link")
		{
			m_IsAnimationEnd = true;
		}
	}
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
	
	if ((StateMachine->GetStateDuration() > 0.5) && _IsPlayed == false)
	{
		SoundPlay(L"sound\\Player\\27(Wind).mp3");
		_IsPlayed = true;
	}
}
void ST_PLAYER_SUPER_BUST_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	_IsPlayed = false;
}
void ST_PLAYER_SUPER_BUST_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	//Super_Bust_Attack
	//Super_Bust_Attack_End
	if (_pState->GetName() == L"Super_Bust_Attack_End")
	{
		ChangeASTMParam(StateMachine, L"Bust", A_FALSE);
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"IsAxe", A_FALSE);
		StateMachine->ChangeScriptParam(L"Super_Bust_Attack", AnimParamType::BOOL, A_FALSE);
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
		StateMachine->ChangeScriptParam(L"Bust_Attack", AnimParamType::BOOL, A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}
}

#pragma endregion

