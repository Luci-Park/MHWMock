#include "pch.h"
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
	_curState = _States.begin()->second;
}

PlayerStateMachine::~PlayerStateMachine()
{
	delete _curState;
	_States.erase(_States.begin(), _States.end());
}

void PlayerStateMachine::ChangeState(std::wstring newState)
{
	if (_curState)
		_curState->Exit(_player,this);
	_curState = _States.find(newState)->second;
	if (_curState)
		_curState->Enter(_player, this);
	
}


void PlayerStateMachine::CreateState()
{
	//Add State
	_States.insert(std::make_pair(L"Idle", new ST_PLAYER_IDLE));
	_States.insert(std::make_pair(L"Move", new ST_PLAYER_MOVE));
	_States.insert(std::make_pair(L"Move_Forward",new ST_PLAYER_MOVE_FORWARD));

}

void PlayerStateMachine::CreateStateParam()
{
	State* st = _States.find(L"Idle")->second;

	//Add state Param
}

void PlayerStateMachine::Tick()
{
	_curState->Tick(_player,this);
}

void PlayerStateMachine::setPlayer(CGameObject* player)
{
	_player = player;
}
