#include "CMainPlayerScript.h"
#include "pch.h"

std::map<std::wstring, State::StateParam> State::_StateParam;

State::State()
{

}
State::~State()
{

}

void State::Enter(CGameObject* player, PlayerStateMachine* StateMachine)
{

}
void State::Tick(CGameObject* player, PlayerStateMachine* StateMachine)
{
}
void State::Exit(CGameObject* player, PlayerStateMachine* StateMachine)
{

}

State::StateParam State::SetParam(std::wstring paramId, AnimParamUnion param)
{
	auto st = _StateParam.find(paramId)->second;
	st._uStateparam = param;
	return st;
}