#include "CMainPlayerScript.h"

PlayerStateMachine::PlayerStateMachine()
	: _curState(nullptr)
	, _player(nullptr)
{

}

PlayerStateMachine::PlayerStateMachine(CGameObject* player)
	: _curState(new ST_PLAYER_IDLE)
	, _player(player)
{
	_curState->Enter(_player);
}

PlayerStateMachine::~PlayerStateMachine()
{
	delete _curState;
}

void PlayerStateMachine::ChangeState(State* newState)
{
	if (_curState)
		_curState->Exit(_player);
	_curState = newState;
	_curState->Enter(_player);
}
void PlayerStateMachine::Tick()
{
	_curState->Tick(_player);
}