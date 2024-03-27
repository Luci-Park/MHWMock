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


		Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
		camFront.y = 0;

		Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		playerFront.y = 0;

		//내적으로 회전값 구함
		//1 ~ -1
		//0~180도까지의 값이 나옴
		auto dot = camFront.Dot(playerFront);

		//외적으로 방향을 구함
		auto cross = camFront.Cross(playerFront);

		
		int dir = CalculateDir(dot, cross.y);
		if (KEY_TAP(KEY::W) && KEY_TAP(KEY::RBTN))
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
		if (KEY_TAP(KEY::D) && KEY_TAP(KEY::RBTN))
		{
			//Sliding Attack R
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
		}
		if (KEY_TAP(KEY::A) && KEY_TAP(KEY::RBTN))
		{
			//Sliding Attack L
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
		}
		if (KEY_TAP(KEY::S) && KEY_TAP(KEY::RBTN))
		{
			//Sliding Attack B
			ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
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
	double duration = StateMachine->GetStateDuration();
	if (duration > 0.5)
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

		Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
		camFront.y = 0;

		Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		playerFront.y = 0;

		//내적으로 회전값 구함
		//1 ~ -1
		//0~180도까지의 값이 나옴
		auto dot = camFront.Dot(playerFront);

		//외적으로 방향을 구함
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
			if (KEY_TAP(KEY::D) && KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack R
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			}
			if (KEY_TAP(KEY::A) && KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack L
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			}
			if (KEY_TAP(KEY::S) && KEY_TAP(KEY::RBTN))
			{
				//Sliding Attack B
				ChangeASTMParam(StateMachine, L"Right_Btn", A_TRUE);
			}
		}
	}

	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
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

}
void ST_PLAYER_WP_BOTTLE_CHARGE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_BOTTLE_CHARGE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

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

}
void ST_PLAYER_WP_CHARGE_K_ENCHENT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_CHARGE_K_ENCHENT::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

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

}
void ST_PLAYER_WP_K_ENCHENT_ATTACK::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_K_ENCHENT_ATTACK::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_K_ENCHENT_ATTACK::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region WP Charge

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

}
void ST_PLAYER_WP_CHARGE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_CHARGE::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

}
#pragma endregion

#pragma region Double Slash

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

}
void ST_PLAYER_WP_DOUBLE_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_DOUBLE_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Upper Slash
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

}
void ST_PLAYER_WP_UPPER_SLASH::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_UPPER_SLASH::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

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

}
void ST_PLAYER_WP_SLIDING_ATTACK_F::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_F::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

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

}
void ST_PLAYER_WP_SLIDING_ATTACK_L::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_L::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

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

}
void ST_PLAYER_WP_SLIDING_ATTACK_B::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

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

}
void ST_PLAYER_WP_SLIDING_ATTACK_R::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_SLIDING_ATTACK_R::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{

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

}

#pragma endregion

