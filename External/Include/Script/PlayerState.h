#pragma once
#include "Engine\CGameObject.h"

class PlayerState
{
private:
public:
	PlayerState();
	virtual ~PlayerState();
public:
	virtual void Enter(CGameObject* player);
	virtual void Tick(CGameObject* player);
	virtual void Exit(CGameObject* player);
};

