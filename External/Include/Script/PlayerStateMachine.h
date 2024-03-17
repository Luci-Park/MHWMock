#pragma once
#include "PlayerState.h"

class PlayerStateMachine
{
private:
	PlayerState* _curState;
	CGameObject* _player;
public:
	PlayerStateMachine();
	PlayerStateMachine(CGameObject* player);
	~PlayerStateMachine();

	void ChangeState(PlayerState* newState);
	void Tick();
};

class Player_ST_Idle : public PlayerState
{
private:
public:
	Player_ST_Idle();
	~Player_ST_Idle();
public:
	virtual void Enter(CGameObject* player) override;
	virtual void Tick(CGameObject* player) override;
	virtual void Exit(CGameObject* player) override;
};