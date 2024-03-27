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
	int iHitDir = StateMachine->GetASTMParam(L"Hit_Dir").INT;
	switch (iHitDir)
	{
	case 0:
		StateMachine->ChangeState(L"N_HIT_F");
		break;
	case 1:
		StateMachine->ChangeState(L"N_HIT_L");
		break;
	case 2:
		StateMachine->ChangeState(L"N_HIT_B");
		break;
	case 3:
		StateMachine->ChangeState(L"N_HIT_R");
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
	m_IsAnimationEnd = false;
}
void ST_PLAYER_N_HIT_F::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"N_Idle");
	}
}
void ST_PLAYER_N_HIT_F::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}

void ST_PLAYER_N_HIT_F::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
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
	m_IsAnimationEnd = false;
}

void ST_PLAYER_N_HIT_L::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"N_Idle");
	}
}

void ST_PLAYER_N_HIT_L::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_N_HIT_L::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
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
	m_IsAnimationEnd = false;
}
void ST_PLAYER_N_HIT_B::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"N_Idle");
	}
}
void ST_PLAYER_N_HIT_B::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_N_HIT_B::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
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
	m_IsAnimationEnd = false;
}

void ST_PLAYER_N_HIT_R::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"N_Idle");
	}
}

void ST_PLAYER_N_HIT_R::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_N_HIT_R::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
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
	int iHitDir = StateMachine->GetASTMParam(L"Hit_Dir").INT;
	switch (iHitDir)
	{
	case 0:
		StateMachine->ChangeState(L"Wp_HIT_F");
		break;
	case 1:
		StateMachine->ChangeState(L"Wp_HIT_L");
		break;
	case 2:
		StateMachine->ChangeState(L"Wp_HIT_B");
		break;
	case 3:
		StateMachine->ChangeState(L"Wp_HIT_R");
		break;
	default:
		break;
	}
}
void ST_PLAYER_WP_HIT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsHit", A_FALSE);
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
	m_IsAnimationEnd = false;
}

void ST_PLAYER_WP_HIT_F::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_Idle");
	}
}

void ST_PLAYER_WP_HIT_F::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_WP_HIT_F::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
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
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_HIT_L::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_HIT_L::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_WP_HIT_L::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
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
	m_IsAnimationEnd = false;
}

void ST_PLAYER_WP_HIT_B::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_Idle");
	}
}

void ST_PLAYER_WP_HIT_B::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_WP_HIT_B::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
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
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_HIT_R::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_Idle");
	}
}
void ST_PLAYER_WP_HIT_R::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_WP_HIT_R::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
}
//-------------------------------------------------------------------------------------
//
//											WP_AXE_HIT
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_AXE_HIT::ST_PLAYER_WP_AXE_HIT()
{

}
ST_PLAYER_WP_AXE_HIT::~ST_PLAYER_WP_AXE_HIT()
{

}
void ST_PLAYER_WP_AXE_HIT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void ST_PLAYER_WP_AXE_HIT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	int iHitDir = StateMachine->GetASTMParam(L"Hit_Dir").INT;
	switch (iHitDir)
	{
	case 0:
		StateMachine->ChangeState(L"Wp_AXE_HIT_F");
		break;
	case 1:
		StateMachine->ChangeState(L"Wp_AXE_HIT_L");
		break;
	case 2:
		StateMachine->ChangeState(L"Wp_AXE_HIT_B");
		break;
	case 3:
		StateMachine->ChangeState(L"Wp_AXE_HIT_R");
		break;
	default:
		break;
	}
}
void ST_PLAYER_WP_AXE_HIT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"IsHit", A_FALSE);
}
//-------------------------------------------------------------------------------------
//
//											WP_AXE_HIT_F
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_AXE_HIT_F::ST_PLAYER_WP_AXE_HIT_F()
{

}

ST_PLAYER_WP_AXE_HIT_F::~ST_PLAYER_WP_AXE_HIT_F()
{

}

void ST_PLAYER_WP_AXE_HIT_F::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = false;
}

void ST_PLAYER_WP_AXE_HIT_F::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
}

void ST_PLAYER_WP_AXE_HIT_F::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_WP_AXE_HIT_F::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
}
//-------------------------------------------------------------------------------------
//
//											WP_AXE_HIT_L
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_AXE_HIT_L::ST_PLAYER_WP_AXE_HIT_L()
{

}
ST_PLAYER_WP_AXE_HIT_L::~ST_PLAYER_WP_AXE_HIT_L()
{

}
void ST_PLAYER_WP_AXE_HIT_L::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_AXE_HIT_L::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
}
void ST_PLAYER_WP_AXE_HIT_L::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_WP_AXE_HIT_L::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
}
//-------------------------------------------------------------------------------------
//
//											WP_AXE_HIT_B
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_AXE_HIT_B::ST_PLAYER_WP_AXE_HIT_B()
{

}

ST_PLAYER_WP_AXE_HIT_B::~ST_PLAYER_WP_AXE_HIT_B()
{

}

void ST_PLAYER_WP_AXE_HIT_B::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = false;
}

void ST_PLAYER_WP_AXE_HIT_B::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
}

void ST_PLAYER_WP_AXE_HIT_B::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_WP_AXE_HIT_B::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
}
//-------------------------------------------------------------------------------------
//
//											WP_AXE_HIT_R
//
//-------------------------------------------------------------------------------------
ST_PLAYER_WP_AXE_HIT_R::ST_PLAYER_WP_AXE_HIT_R()
{

}
ST_PLAYER_WP_AXE_HIT_R::~ST_PLAYER_WP_AXE_HIT_R()
{

}
void ST_PLAYER_WP_AXE_HIT_R::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	m_IsAnimationEnd = false;
}
void ST_PLAYER_WP_AXE_HIT_R::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (m_IsAnimationEnd)
	{
		StateMachine->ChangeState(L"Wp_AXE_Idle");
	}
}
void ST_PLAYER_WP_AXE_HIT_R::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	ChangeASTMParam(StateMachine, L"Hit_Dir", A_NONE);
}
void ST_PLAYER_WP_AXE_HIT_R::OnAnimationEndStart(IAnimationState* _pState)
{
	m_IsAnimationEnd = true;
}
#pragma endregion
