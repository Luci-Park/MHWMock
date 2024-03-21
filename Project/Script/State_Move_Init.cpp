
#include "pch.h"
#include "CMainPlayerScript.h"

//-------------------------------------------------------------------------------------
//
//										MOVE FORWARD
//
//-------------------------------------------------------------------------------------

ST_PLAYER_MOVE_FORWARD::ST_PLAYER_MOVE_FORWARD()
{

}

ST_PLAYER_MOVE_FORWARD::~ST_PLAYER_MOVE_FORWARD()
{

}

void ST_PLAYER_MOVE_FORWARD::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void ST_PLAYER_MOVE_FORWARD::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
	if (KEY_RELEASE(KEY::W))
	{
		//Move Forward
		StateMachine->ChangeState(L"Idle");
	}
	if (KEY_PRESSED(KEY::A))
	{
		//rotate Left
		Quaternion rot = player->Transform()->GetRelativeRot();
		player->Transform()->GetRelativeEulerRot();
	}
	if (KEY_PRESSED(KEY::S))
	{
		//Change State Move Backward
	}
	if (KEY_PRESSED(KEY::D))
	{
		//Move Right
	}
}
void ST_PLAYER_MOVE_FORWARD::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{
	int a = 0;
}