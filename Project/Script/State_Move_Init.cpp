#include "pch.h"
#include "CMainPlayerScript.h"

#pragma region N_MOVE

#pragma region N_Move_STATE
//-------------------------------------------------------------------------------------
//
//											N_MOVE
//
//-------------------------------------------------------------------------------------

ST_PLAYER_N_MOVE::ST_PLAYER_N_MOVE()
{

}
ST_PLAYER_N_MOVE::~ST_PLAYER_N_MOVE()
{

}

void ST_PLAYER_N_MOVE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetCamera() == nullptr)
		return;

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

	if (KEY_PRESSED(KEY::W))			//Move Forward
	{
		int dir = CalculateDir(dot,cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::A))		//Move Left
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD );
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::S))		//Move Backward
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT );
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::D))		//Move Right	
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT );
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		default:
			break;
		}
	}

	ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
}
void ST_PLAYER_N_MOVE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	auto Param = StateMachine->GetASTMParam(L"Dir");
	int Dir = Param.INT;
	switch (Dir)
	{
	case 0:
		StateMachine->ChangeState(L"N_Move_Forward");
		break;
	case 1:
		StateMachine->ChangeState(L"N_Move_Left");
		break;
	case 2:
		StateMachine->ChangeState(L"N_Move_Backward");
		break;
	case 3:
		StateMachine->ChangeState(L"N_Move_Right");
		break;
	default:
		break;
	}
}
void ST_PLAYER_N_MOVE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region N_MOVE_FORWARD
//-------------------------------------------------------------------------------------
//
//									N	MOVE FORWARD
//
//-------------------------------------------------------------------------------------

ST_PLAYER_N_MOVE_FORWARD::ST_PLAYER_N_MOVE_FORWARD()
{

}

ST_PLAYER_N_MOVE_FORWARD::~ST_PLAYER_N_MOVE_FORWARD()
{

}

void ST_PLAYER_N_MOVE_FORWARD::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_N_MOVE_FORWARD::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{

	if (KEY_TAP(KEY::LBTN))
	{
		ChangeASTMParam(StateMachine, L"Wp_on", A_TRUE);
		ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
		ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	//정지
	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Move Forward
			ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
			ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
			StateMachine->ChangeState(L"N_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsRun", A_TRUE);
		ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
	}

	if (KEY_RELEASE(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"N_Idle");
	}
}
void ST_PLAYER_N_MOVE_FORWARD::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
}

#pragma endregion

#pragma region N_MVOVE_LEFT
//-------------------------------------------------------------------------------------
//
//										MOVE LEFT
//
//-------------------------------------------------------------------------------------


ST_PLAYER_N_MOVE_LEFT::ST_PLAYER_N_MOVE_LEFT()
{

}

ST_PLAYER_N_MOVE_LEFT::~ST_PLAYER_N_MOVE_LEFT()
{

}

void ST_PLAYER_N_MOVE_LEFT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_MOVE_LEFT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A)||KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop Move
			ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
			ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
			StateMachine->ChangeState(L"N_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsRun", A_TRUE);
		ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
	}

	if (KEY_RELEASE(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"N_Idle");
	}
}

void ST_PLAYER_N_MOVE_LEFT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
#pragma endregion

#pragma region N_MOVE_BACKWARD
//-------------------------------------------------------------------------------------
//
//										MOVE BACKWARD
//
//-------------------------------------------------------------------------------------

ST_PLAYER_N_MOVE_Backward::ST_PLAYER_N_MOVE_Backward()
{

}
ST_PLAYER_N_MOVE_Backward::~ST_PLAYER_N_MOVE_Backward()
{

}

void ST_PLAYER_N_MOVE_Backward::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_MOVE_Backward::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop Move
			ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
			ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
			StateMachine->ChangeState(L"N_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsRun", A_TRUE);
		ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
	}

	if (KEY_RELEASE(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"N_Idle");
	}
}

void ST_PLAYER_N_MOVE_Backward::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region N_MOVE_RIGHT
//-------------------------------------------------------------------------------------
//
//										MOVE RIGHT
//
//-------------------------------------------------------------------------------------

ST_PLAYER_N_MOVE_Right::ST_PLAYER_N_MOVE_Right()
{

}
ST_PLAYER_N_MOVE_Right::~ST_PLAYER_N_MOVE_Right()
{

}

void ST_PLAYER_N_MOVE_Right::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_N_MOVE_Right::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop Move
			ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
			ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
			StateMachine->ChangeState(L"N_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsRun", A_TRUE);
		ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
	}

	if (KEY_RELEASE(KEY::LSHIFT))
	{
		ChangeASTMParam(StateMachine, L"IsRun", A_FALSE);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"N_Idle");
	}
}

void ST_PLAYER_N_MOVE_Right::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma endregion

#pragma region Wp_Move

#pragma region Wp_Move_State

ST_PLAYER_WP_MOVE::ST_PLAYER_WP_MOVE()
{

}
ST_PLAYER_WP_MOVE::~ST_PLAYER_WP_MOVE()
{

}

void ST_PLAYER_WP_MOVE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetCamera() == nullptr)
		return;

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

	if (KEY_PRESSED(KEY::W))			//Move Forward
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::A))		//Move Left
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::S))		//Move Backward
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT );
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::D))		//Move Right	
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		default:
			break;
		}
	}
}
void ST_PLAYER_WP_MOVE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	auto Param = StateMachine->GetASTMParam(L"Dir");
	int Dir = Param.INT;
	switch (Dir)
	{
	case 0:
		StateMachine->ChangeState(L"Wp_Move_Forward");
		break;
	case 1:
		StateMachine->ChangeState(L"Wp_Move_Left");
		break;
	case 2:
		ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
		StateMachine->ChangeState(L"Wp_Move_Backward");
		break;
	case 3:
		StateMachine->ChangeState(L"Wp_Move_Right");
		break;
	default:
		break;
	}
}
void ST_PLAYER_WP_MOVE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Wp_Move_Forward

ST_PLAYER_WP_MOVE_Forward::ST_PLAYER_WP_MOVE_Forward()
{

}
ST_PLAYER_WP_MOVE_Forward::~ST_PLAYER_WP_MOVE_Forward()
{

}
void ST_PLAYER_WP_MOVE_Forward::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_MOVE_Forward::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop
			ChangeASTMParam(StateMachine, L"IsMove", A_FALSE);
			StateMachine->ChangeState(L"Wp_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}
}

void ST_PLAYER_WP_MOVE_Forward::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Wp_Move_Left

ST_PLAYER_WP_MOVE_Left::ST_PLAYER_WP_MOVE_Left()
{

}
ST_PLAYER_WP_MOVE_Left::~ST_PLAYER_WP_MOVE_Left()
{

}
void ST_PLAYER_WP_MOVE_Left::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_MOVE_Left::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop
			ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
			StateMachine->ChangeState(L"Wp_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}
}

void ST_PLAYER_WP_MOVE_Left::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Wp_Move_Right

ST_PLAYER_WP_MOVE_Right::ST_PLAYER_WP_MOVE_Right()
{

}
ST_PLAYER_WP_MOVE_Right::~ST_PLAYER_WP_MOVE_Right()
{

}
void ST_PLAYER_WP_MOVE_Right::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_WP_MOVE_Right::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop
			ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
			StateMachine->ChangeState(L"Wp_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}
}

void ST_PLAYER_WP_MOVE_Right::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Wp_Move_Backward

ST_PLAYER_WP_MOVE_Backward::ST_PLAYER_WP_MOVE_Backward()
{

}
ST_PLAYER_WP_MOVE_Backward::~ST_PLAYER_WP_MOVE_Backward()
{

}
void ST_PLAYER_WP_MOVE_Backward::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	Vec3 rot = player->Transform()->GetRelativeEulerRot();
	rot.y += 180;
	player->Transform()->SetRelativeRot(rot);
}

void ST_PLAYER_WP_MOVE_Backward::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_TAP(KEY::SPACE))
	{
		ChangeASTMParam(StateMachine, L"Rolling_Tg", A_TRUE);
		StateMachine->ChangeState(L"Wp_Idle");
	}

	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop
			ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
			StateMachine->ChangeState(L"Wp_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}
}

void ST_PLAYER_WP_MOVE_Backward::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma endregion

#pragma region Wp_Axe_Move

#pragma region AXE Move State

ST_PLAYER_AXE_MOVE::ST_PLAYER_AXE_MOVE()
{

}
ST_PLAYER_AXE_MOVE::~ST_PLAYER_AXE_MOVE()
{

}

void ST_PLAYER_AXE_MOVE::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (StateMachine->GetCamera() == nullptr)
		return;

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

	if (KEY_PRESSED(KEY::W))			//Move Forward
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::A))		//Move Left
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::S))		//Move Backward
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		default:
			break;
		}
	}
	else if (KEY_PRESSED(KEY::D))		//Move Right	
	{
		int dir = CalculateDir(dot, cross.y);
		switch (dir)
		{
		case A_F:
			ChangeASTMParam(StateMachine, L"Dir", A_LEFT);
			break;
		case A_L:
			ChangeASTMParam(StateMachine, L"Dir", A_FORWARD);
			break;
		case A_B:
			ChangeASTMParam(StateMachine, L"Dir", A_RIGHT);
			break;
		case A_R:
			ChangeASTMParam(StateMachine, L"Dir", A_BACKWARD);
			break;
		default:
			break;
		}
	}
}
void ST_PLAYER_AXE_MOVE::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	auto Param = StateMachine->GetASTMParam(L"Dir");
	int Dir = Param.INT;
	switch (Dir)
	{
	case 0:
		StateMachine->ChangeState(L"Wp_AXE_Move_Forward");
		break;
	case 1:
		StateMachine->ChangeState(L"Wp_AXE_Move_Left");
		break;
	case 2:
		StateMachine->ChangeState(L"Wp_AXE_Move_Backward");
		break;
	case 3:
		StateMachine->ChangeState(L"Wp_AXE_Move_Right");
		break;
	default:
		break;
	}
}
void ST_PLAYER_AXE_MOVE::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}


#pragma endregion

#pragma region Wp_Axe_Move_Left
ST_PLAYER_AXE_MOVE_LEFT::ST_PLAYER_AXE_MOVE_LEFT()
{

}
ST_PLAYER_AXE_MOVE_LEFT::~ST_PLAYER_AXE_MOVE_LEFT()
{

}
void ST_PLAYER_AXE_MOVE_LEFT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_AXE_MOVE_LEFT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop
			ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
			StateMachine->ChangeState(L"Wp_AXE_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}
}

void ST_PLAYER_AXE_MOVE_LEFT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
#pragma endregion

#pragma region Axe Move Right
ST_PLAYER_AXE_MOVE_RIGHT::ST_PLAYER_AXE_MOVE_RIGHT()
{

}
ST_PLAYER_AXE_MOVE_RIGHT::~ST_PLAYER_AXE_MOVE_RIGHT()
{

}
void ST_PLAYER_AXE_MOVE_RIGHT::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_AXE_MOVE_RIGHT::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop
			ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
			StateMachine->ChangeState(L"Wp_AXE_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}
}

void ST_PLAYER_AXE_MOVE_RIGHT::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
#pragma endregion

#pragma region Axe Move Forward

ST_PLAYER_AXE_MOVE_FORWARD::ST_PLAYER_AXE_MOVE_FORWARD()
{

}
ST_PLAYER_AXE_MOVE_FORWARD::~ST_PLAYER_AXE_MOVE_FORWARD()
{

}
void ST_PLAYER_AXE_MOVE_FORWARD::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_AXE_MOVE_FORWARD::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop
			ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
			StateMachine->ChangeState(L"Wp_AXE_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}
}

void ST_PLAYER_AXE_MOVE_FORWARD::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma region Axe Move Backward

ST_PLAYER_AXE_MOVE_BACKWARD::ST_PLAYER_AXE_MOVE_BACKWARD()
{

}
ST_PLAYER_AXE_MOVE_BACKWARD::~ST_PLAYER_AXE_MOVE_BACKWARD()
{

}
void ST_PLAYER_AXE_MOVE_BACKWARD::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

void ST_PLAYER_AXE_MOVE_BACKWARD::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::A) || KEY_RELEASE(KEY::W)
		|| KEY_RELEASE(KEY::S) || KEY_RELEASE(KEY::D))
	{
		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::W)
			|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
		{

		}
		else
		{
			//Stop
			ChangeASTMParam(StateMachine, L"IsMove", (AnimParamUnion)false);
			StateMachine->ChangeState(L"Wp_AXE_Idle");
		}
	}

	Vec3 camFront = StateMachine->GetCamera()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	camFront.y = 0;

	Vec3 playerFront = player->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	playerFront.y = 0;

	auto dot = camFront.Dot(playerFront);

	//외적으로 방향을 구함
	auto cross = camFront.Cross(playerFront);
	int camdir = CalculateDir(dot, cross.y);

	if (KEY_PRESSED(KEY::W))
	{
		//B 면 아무것도 안하고 
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::A))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//rotate Left
	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_R:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_L:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec3 rot = player->Transform()->GetRelativeEulerRot();
		switch (camdir)
		{
		case A_F:
			rot.y -= 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		case A_B:
			rot.y += 45 * CTimeMgr::GetInst()->GetDeltaTime();
			player->Transform()->SetRelativeRot(rot);
			break;
		default:
			break;
		}
		//Move Right
	}
}

void ST_PLAYER_AXE_MOVE_BACKWARD::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

#pragma endregion

#pragma endregion
