#include "CMainPlayerScript.h"
#include "pch.h"

std::map<std::wstring, State::StateParam> State::_StateParam;

State::State()
	: m_IsAnimationEnd(false)
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

void State::AddParam(std::wstring paramId, AnimParamUnion Stateparamunion, AnimParamType Stateparamtype)
{
	StateParam temp;
	temp._eStateparam = Stateparamtype;
	temp._uStateparam = Stateparamunion;
	_StateParam.insert(make_pair(paramId, temp));
}

State::StateParam State::SetParam(std::wstring paramId, AnimParamUnion param)
{
	auto st = _StateParam.find(paramId)->second;
	st._uStateparam = param;
	return st;
}

void State::ChangeASTMParam(PlayerStateMachine* PSM, std::wstring paramId, AnimParamUnion param)
{
	StateParam sp = SetParam(paramId, param);
	PSM->SetASTMParam(paramId, sp._eStateparam, sp._uStateparam);
}

AnimParamUnion State::GetParam(std::wstring paramId, PlayerStateMachine* PSM)
{
	PSM->GetParam(paramId);
	auto st = _StateParam.find(paramId)->second;
	return st._uStateparam;
}

double State::GetStateDuration(PlayerStateMachine* PSM)
{
	return PSM->GetStateDuration();
}