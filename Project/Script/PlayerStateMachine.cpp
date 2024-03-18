#include "CMainPlayerScript.h"

PlayerStateMachine::PlayerStateMachine()
	: _curState(nullptr)
	, _player(nullptr)
{

}

PlayerStateMachine::PlayerStateMachine(CGameObject* player)
	: _curState(nullptr)
	, _player(player)
{
	CreateState();
	_curState = _States[0];
}

PlayerStateMachine::~PlayerStateMachine()
{
	delete _curState;
}

void PlayerStateMachine::ChangeState(Event newState)
{
	if (_curState)
		_curState->Exit(_player,this);
	_curState = _States[(UINT)newState];
	if (_curState)
		_curState->Enter(_player, this);
}
void PlayerStateMachine::CreateState()
{
	//_States.assign((UINT)Event::END, nullptr);
	_States.push_back(new ST_PLAYER_IDLE);
	_States.push_back(new ST_PLAYER_MOVE);
	_States.push_back(new ST_PLAYER_MOVE_FORWARD);
}
void PlayerStateMachine::Tick()
{
	_curState->Tick(_player,this);
}