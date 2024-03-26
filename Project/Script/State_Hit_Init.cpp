#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region N_HIT

//-------------------------------------------------------------------------------------
//
//											N_HIT
//
//-------------------------------------------------------------------------------------
ST_PLAYER_N_HIT::ST_PLAYER_N_HIT()
{

}

ST_PLAYER_N_HIT::~ST_PLAYER_N_HIT()
{

}

void ST_PLAYER_N_HIT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	
}

void ST_PLAYER_N_HIT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	int iHitDir = GetParam(L"Hit_Dir", StateMachine).INT;
	switch (iHitDir)
	{
	case 0:
		StateMachine->ChangeState(L"ST_PLAYER_N_HIT_F");
		break;
	case 1:
		StateMachine->ChangeState(L"ST_PLAYER_N_HIT_F");
		break;
	case 2:
		StateMachine->ChangeState(L"ST_PLAYER_N_HIT_F");
		break;
	case 3:
		StateMachine->ChangeState(L"ST_PLAYER_N_HIT_F");
		break;
	case 4:
		StateMachine->ChangeState(L"ST_PLAYER_N_HIT_F");
		break;
	default:
		break;
	}
}

void ST_PLAYER_N_HIT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsHit", A_FALSE);
}

//-------------------------------------------------------------------------------------
//
//											N_HIT_F
//
//-------------------------------------------------------------------------------------
ST_PLAYER_N_HIT_F::ST_PLAYER_N_HIT_F()
{

}
ST_PLAYER_N_HIT_F::~ST_PLAYER_N_HIT_F()
{

}
void ST_PLAYER_N_HIT_F::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_N_HIT_F::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_N_HIT_F::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
//-------------------------------------------------------------------------------------
//
//											N_HIT_L
//
//-------------------------------------------------------------------------------------
ST_PLAYER_N_HIT_L::ST_PLAYER_N_HIT_L()
{

}

ST_PLAYER_N_HIT_L::~ST_PLAYER_N_HIT_L()
{

}

void ST_PLAYER_N_HIT_L::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_HIT_L::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_HIT_L::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsHit", A_FALSE);
}

//-------------------------------------------------------------------------------------
//
//											N_HIT_B
//
//-------------------------------------------------------------------------------------
ST_PLAYER_N_HIT_B::ST_PLAYER_N_HIT_B()
{

}
ST_PLAYER_N_HIT_B::~ST_PLAYER_N_HIT_B()
{

}
void ST_PLAYER_N_HIT_B::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_N_HIT_B::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_N_HIT_B::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
//-------------------------------------------------------------------------------------
//
//											N_HIT_R
//
//-------------------------------------------------------------------------------------
ST_PLAYER_N_HIT_R::ST_PLAYER_N_HIT_R()
{

}

ST_PLAYER_N_HIT_R::~ST_PLAYER_N_HIT_R()
{

}

void ST_PLAYER_N_HIT_R::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_HIT_R::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_HIT_R::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsHit", A_FALSE);
}

//-------------------------------------------------------------------------------------
//
//											WP_HIT
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_HIT::ST_PLAYER_WP_HIT()
{

}
ST_PLAYER_WP_HIT::~ST_PLAYER_WP_HIT()
{

}
void ST_PLAYER_WP_HIT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_HIT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_HIT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
//-------------------------------------------------------------------------------------
//
//											WP_HIT_F
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_HIT_F::ST_PLAYER_WP_HIT_F()
{

}

ST_PLAYER_WP_HIT_F::~ST_PLAYER_WP_HIT_F()
{

}

void ST_PLAYER_WP_HIT_F::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_HIT_F::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_HIT_F::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsHit", A_FALSE);
}

//-------------------------------------------------------------------------------------
//
//											WP_HIT_L
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_HIT_L::ST_PLAYER_WP_HIT_L()
{

}
ST_PLAYER_WP_HIT_L::~ST_PLAYER_WP_HIT_L()
{

}
void ST_PLAYER_WP_HIT_L::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_HIT_L::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_HIT_L::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
//-------------------------------------------------------------------------------------
//
//											WP_HIT_B
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_HIT_B::ST_PLAYER_WP_HIT_B()
{

}

ST_PLAYER_WP_HIT_B::~ST_PLAYER_WP_HIT_B()
{

}

void ST_PLAYER_WP_HIT_B::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_HIT_B::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_HIT_B::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsHit", A_FALSE);
}

//-------------------------------------------------------------------------------------
//
//											WP_HIT_R
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_HIT_R::ST_PLAYER_WP_HIT_R()
{

}
ST_PLAYER_WP_HIT_R::~ST_PLAYER_WP_HIT_R()
{

}
void ST_PLAYER_WP_HIT_R::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_HIT_R::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_HIT_R::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
#pragma endregion
