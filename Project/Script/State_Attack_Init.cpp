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
void ST_PLAYER_WP_ATTACK_COMBOSLASH_01::OnAnimationEndStart(IAnimationState* _pState)
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
void ST_PLAYER_WP_ATTACK_COMBOSLASH_02::OnAnimationEndStart(IAnimationState* _pState)
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
void ST_PLAYER_WP_ATTACK_COMBOSLASH_03::OnAnimationEndStart(IAnimationState* _pState)
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