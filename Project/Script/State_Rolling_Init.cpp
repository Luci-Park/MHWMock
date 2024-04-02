#include "pch.h"
#include "CMainPlayerScript.h"
//-------------------------------------------------------------------------------------
//
//											N_ROLLING
//
//-------------------------------------------------------------------------------------
ST_PLAYER_N_ROLLING::ST_PLAYER_N_ROLLING()
{
}
ST_PLAYER_N_ROLLING::~ST_PLAYER_N_ROLLING()
{
}

void ST_PLAYER_N_ROLLING::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_N_ROLLING::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"N_Idle");
	}
}
void ST_PLAYER_N_ROLLING::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_N_ROLLING::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"N_Rolling")
		m_IsAnimationEnd = true;
}

//-------------------------------------------------------------------------------------
//
//											WP_ROLLING
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_ROLLING::ST_PLAYER_WP_ROLLING()
{
}
ST_PLAYER_WP_ROLLING::~ST_PLAYER_WP_ROLLING()
{
}

void ST_PLAYER_WP_ROLLING::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	auto cross = camFront.Cross(playerFront);

	int dir = CalculateDir(dot, cross.y);
	auto rot = player->Transform()->GetRelativeEulerRot();
	if (KEY_PRESSED(KEY::W))
	{
		switch (dir)
		{
		case A_F:
			rot.y -= 180;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_R:
			rot.y += 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
	}
	if (KEY_PRESSED(KEY::A))
	{
		switch (dir)
		{
		case A_F:
			rot.y += 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 180;
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
	}
	if (KEY_PRESSED(KEY::S))
	{
		switch (dir)
		{
		case A_L:
			rot.y += 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 180;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_R:
			rot.y -= 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
	}
	if (KEY_PRESSED(KEY::D))
	{
		switch (dir)
		{
		case A_F:
			rot.y -= 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_R:
			rot.y += 180;
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
	}

	ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
	ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
}
void ST_PLAYER_WP_ROLLING::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		ChangeASTMParam(StateMachine, L"Dir", A_4);
		ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
		StateMachine->IsInput();
	}
}
void ST_PLAYER_WP_ROLLING::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_ROLLING::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"wp_Rolling")
		m_IsAnimationEnd = true;
}
//-------------------------------------------------------------------------------------
//
//											WP_AXE_ROLLING
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_AXE_ROLLING::ST_PLAYER_WP_AXE_ROLLING()
{
}
ST_PLAYER_WP_AXE_ROLLING::~ST_PLAYER_WP_AXE_ROLLING()
{
}
void ST_PLAYER_WP_AXE_ROLLING::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	auto cross = camFront.Cross(playerFront);

	int dir = CalculateDir(dot, cross.y);
	auto rot = player->Transform()->GetRelativeEulerRot();
	if (KEY_PRESSED(KEY::W))
	{
		switch (dir)
		{
		case A_F:
			rot.y -= 180;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_R:
			rot.y += 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
	}
	if (KEY_PRESSED(KEY::A))
	{
		switch (dir)
		{
		case A_F:
			rot.y += 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 180;
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
	}
	if (KEY_PRESSED(KEY::S))
	{
		switch (dir)
		{
		case A_L:
			rot.y += 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 180;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_R:
			rot.y -= 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
	}
	if (KEY_PRESSED(KEY::D))
	{
		switch (dir)
		{
		case A_F:
			rot.y -= 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 90;
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_R:
			rot.y += 180;
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
	}

	ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
	ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
}
void ST_PLAYER_WP_AXE_ROLLING::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		ChangeASTMParam(StateMachine, L"IsAttack", A_FALSE);
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
}
void ST_PLAYER_WP_AXE_ROLLING::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_WP_AXE_ROLLING::OnAnimationEndStart(IAnimationState* _pState, PlayerStateMachine* StateMachine)
{
	if (_pState->GetName() == L"Wp_axe_Rolling")
		m_IsAnimationEnd = true;
}