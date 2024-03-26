#include "pch.h"
#include "CMainPlayerScript.h"

class State;
PlayerStateMachine::PlayerStateMachine()
	: _curState(nullptr)
	, _player(nullptr)
	, _ASTM(nullptr)
{

}

PlayerStateMachine::PlayerStateMachine(CGameObject* player)
	: _curState(nullptr)
	, _player(player)
	, _ASTM(nullptr)
{
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


void PlayerStateMachine::Begin()
{
	CreateState();
	_curState = _States.find(L"N_Idle")->second;
	_ASTM = _player->Animator3D()->GetStateMachine();
	CreateStateParam();

}

void PlayerStateMachine::CreateState()
{
	//Add State
	_States.insert(std::make_pair(L"N_Idle", new ST_PLAYER_N_IDLE));
	_States.insert(std::make_pair(L"N_Move", new ST_PLAYER_N_MOVE));
	_States.insert(std::make_pair(L"N_Move_Forward",new ST_PLAYER_N_MOVE_FORWARD));
	_States.insert(std::make_pair(L"N_Move_Left",new ST_PLAYER_N_MOVE_LEFT));
	_States.insert(std::make_pair(L"N_Move_Backward",new ST_PLAYER_N_MOVE_Backward));
	_States.insert(std::make_pair(L"N_Move_Right",new ST_PLAYER_N_MOVE_Right));

	_States.insert(std::make_pair(L"N_HIT",new ST_PLAYER_N_HIT));
	_States.insert(std::make_pair(L"N_HIT_F",new ST_PLAYER_N_HIT_F));
	//_States.insert(std::make_pair(L"N_HIT_L",new ST_PLAYER_N_HIT_L));
	//_States.insert(std::make_pair(L"N_HIT_B",new ST_PLAYER_N_HIT_B));
	//_States.insert(std::make_pair(L"N_HIT_R",new ST_PLAYER_N_HIT_R));
	//_States.insert(std::make_pair(L"N_Rolling",new ST_PLAYER_N_ROLLING));

	_States.insert(std::make_pair(L"Wp_Idle",new ST_PLAYER_WP_IDLE));	
	_States.insert(std::make_pair(L"Wp_Move",new ST_PLAYER_WP_MOVE));	
	_States.insert(std::make_pair(L"Wp_Move_Left",new ST_PLAYER_WP_MOVE_Left));	
	_States.insert(std::make_pair(L"Wp_Move_Right",new ST_PLAYER_WP_MOVE_Right));	
	_States.insert(std::make_pair(L"Wp_Move_Backward",new ST_PLAYER_WP_MOVE_Backward));	
	_States.insert(std::make_pair(L"Wp_Move_Forward",new ST_PLAYER_WP_MOVE_Forward));	
}

double PlayerStateMachine::GetStateDuration()
{
	_ASTM->GetHead()->OnTransitionEnd();
	return _ASTM->GetTickPercent();
}

void PlayerStateMachine::CreateStateParam()
{
	//Add state Param
	CAnimationStateMachine* st = _player->Animator3D()->GetStateMachine();
	State* s = _States.find(L"N_Idle")->second;
	for(auto t : st->GetAllParams())
	{
		s->AddParam(t->name, t->value, t->type);
	}
}

void PlayerStateMachine::Tick()
{
	_curState->Tick(_player,this);
}

void PlayerStateMachine::setPlayer(CGameObject* player)
{
	_player = player;
}

void PlayerStateMachine::SetASTMParam(std::wstring paramId, AnimParamType type, AnimParamUnion param)
{
	switch (type)
	{
	case AnimParamType::FLOAT:
		_ASTM->SetFloat(paramId, param.FLOAT);
		break;
	case AnimParamType::INT:
		_ASTM->SetInt(paramId, param.INT);
		break;
	case AnimParamType::BOOL:
		_ASTM->SetBool(paramId, param.BOOL);
		break;
	case AnimParamType::TRIGGER:
		_ASTM->SetTrigger(paramId, param.TRIGGER);
		break;
	case AnimParamType::NONE:
		break;
	default:
		break;
	}
}

void PlayerStateMachine::ChangeASTMParam(std::wstring paramId, AnimParamUnion param)
{
	_curState->ChangeASTMParam(this, paramId, param);
}

AnimParamUnion PlayerStateMachine::GetParam(std::wstring paramId)
{
	//return _curState->GetParam(paramId);
	return A_TRUE;
}

AnimParamUnion PlayerStateMachine::GetASTMParam(std::wstring paramId)
{
	return _ASTM->GetParamByName(paramId)->value;
}

