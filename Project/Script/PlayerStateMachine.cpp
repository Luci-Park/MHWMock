#include "pch.h"
#include "CMainPlayerScript.h"
#include "CSwordScript.h"
#include "CPlayerShieldScript.h"

class State;
PlayerStateMachine::PlayerStateMachine()
	: _curState(nullptr)
	, _player(nullptr)
	, _ASTM(nullptr)
	, _Camera(nullptr)
	, _Shield(nullptr)
	, _Sword(nullptr)
{

}

PlayerStateMachine::PlayerStateMachine(CGameObject* player)
	: _curState(nullptr)
	, _player(player)
	, _ASTM(nullptr)
	, _Camera(nullptr)
	, _Shield(nullptr)
	, _Sword(nullptr)
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
	_curState->ReSet();
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
	_States.insert(std::make_pair(L"N_HIT_L",new ST_PLAYER_N_HIT_L));
	_States.insert(std::make_pair(L"N_HIT_B",new ST_PLAYER_N_HIT_B));
	_States.insert(std::make_pair(L"N_HIT_R",new ST_PLAYER_N_HIT_R));
	
	_States.insert(std::make_pair(L"N_Rolling",new ST_PLAYER_N_ROLLING));
	_States.insert(std::make_pair(L"Wp_Rolling",new ST_PLAYER_WP_ROLLING));
	_States.insert(std::make_pair(L"Wp_AXE_Rolling",new ST_PLAYER_WP_AXE_ROLLING));
	
	_States.insert(std::make_pair(L"Wp_Idle",new ST_PLAYER_WP_IDLE));	
	_States.insert(std::make_pair(L"Wp_Move",new ST_PLAYER_WP_MOVE));	
	_States.insert(std::make_pair(L"Wp_Move_Left",new ST_PLAYER_WP_MOVE_Left));	
	_States.insert(std::make_pair(L"Wp_Move_Right",new ST_PLAYER_WP_MOVE_Right));	
	_States.insert(std::make_pair(L"Wp_Move_Backward",new ST_PLAYER_WP_MOVE_Backward));	
	_States.insert(std::make_pair(L"Wp_Move_Forward",new ST_PLAYER_WP_MOVE_Forward));	
	
	_States.insert(std::make_pair(L"Wp_Guard",new ST_PLAYER_WP_GUARD));
	_States.insert(std::make_pair(L"Wp_Guard_On",new ST_PLAYER_WP_GUARD_ON));
	_States.insert(std::make_pair(L"Wp_Guard_Idle",new ST_PLAYER_WP_GUARD_IDLE));
	_States.insert(std::make_pair(L"Wp_Guard_Off",new ST_PLAYER_WP_GUARD_OFF));
	
	_States.insert(std::make_pair(L"Wp_Attack", new ST_PLAYER_WP_ATTACK));
	_States.insert(std::make_pair(L"Wp_Attack_ComboSlash_01", new ST_PLAYER_WP_ATTACK_COMBOSLASH_01));
	_States.insert(std::make_pair(L"Wp_Attack_ComboSlash_02", new ST_PLAYER_WP_ATTACK_COMBOSLASH_02));
	_States.insert(std::make_pair(L"Wp_Attack_ComboSlash_03", new ST_PLAYER_WP_ATTACK_COMBOSLASH_03));

	_States.insert(std::make_pair(L"Wp_Sheld_Attack", new ST_PLAYER_WP_SHELD_ATTACK));
	_States.insert(std::make_pair(L"Wp_Dash_Attack", new ST_PLAYER_WP_DASH_ATTACK));

	_States.insert(std::make_pair(L"Wp_Bottle_Charge", new ST_PLAYER_WP_BOTTLE_CHARGE));
	_States.insert(std::make_pair(L"Wp_Charge_K_Enchent", new ST_PLAYER_WP_CHARGE_K_ENCHENT));
	_States.insert(std::make_pair(L"Wp_K_Enchent_Attack", new ST_PLAYER_WP_K_ENCHENT_ATTACK));

	_States.insert(std::make_pair(L"Wp_Charge", new ST_PLAYER_WP_CHARGE));
	_States.insert(std::make_pair(L"Wp_Double_Slash", new ST_PLAYER_WP_DOUBLE_SLASH));
	_States.insert(std::make_pair(L"Wp_Upper_Slash", new ST_PLAYER_WP_UPPER_SLASH));

	_States.insert(std::make_pair(L"Wp_Sliding_Attack_F", new ST_PLAYER_WP_SLIDING_ATTACK_F));
	_States.insert(std::make_pair(L"Wp_Sliding_Attack_L", new ST_PLAYER_WP_SLIDING_ATTACK_L));
	_States.insert(std::make_pair(L"Wp_Sliding_Attack_B", new ST_PLAYER_WP_SLIDING_ATTACK_B));
	_States.insert(std::make_pair(L"Wp_Sliding_Attack_R", new ST_PLAYER_WP_SLIDING_ATTACK_R));

	_States.insert(std::make_pair(L"Wp_HIT", new ST_PLAYER_WP_HIT));
	_States.insert(std::make_pair(L"Wp_HIT_F", new ST_PLAYER_WP_HIT_F));
	_States.insert(std::make_pair(L"Wp_HIT_L", new ST_PLAYER_WP_HIT_L));
	_States.insert(std::make_pair(L"Wp_HIT_B", new ST_PLAYER_WP_HIT_B));
	_States.insert(std::make_pair(L"Wp_HIT_R", new ST_PLAYER_WP_HIT_R));

	_States.insert(std::make_pair(L"Wp_SWITCH", new ST_PLAYER_WP_SWITCH));
	_States.insert(std::make_pair(L"Wp_SWITCH_KNIFE_TO_AXE", new ST_PLAYER_WP_SWITCH_KNIFE_TO_AXE));
	_States.insert(std::make_pair(L"Wp_SWITCH_AXE_TO_KNIFE", new ST_PLAYER_WP_SWITCH_AXE_TO_KNIFE));

	_States.insert(std::make_pair(L"Wp_AXE_Idle", new ST_PLAYER_AXE_IDLE));

	_States.insert(std::make_pair(L"Wp_AXE_Attack", new ST_PLAYER_WP_AXE_ATTACK));
	_States.insert(std::make_pair(L"Wp_AXE_Upper_Slash", new ST_PLAYER_AXE_UPPER_SLASH));
	_States.insert(std::make_pair(L"Wp_AXE_Down_Slash", new ST_PLAYER_AXE_DOWN_SLASH));
	_States.insert(std::make_pair(L"Wp_AXE_Horizontal_Slash", new ST_PLAYER_AXE_HORIZONTAL_SLASH));
	_States.insert(std::make_pair(L"Wp_AXE_Turnning_Slash", new ST_PLAYER_AXE_TURNNING_SLASH));
	_States.insert(std::make_pair(L"Wp_AXE_Down_to_Up_Link", new ST_PLAYER_AXE_DOWN_To_UP));

	_States.insert(std::make_pair(L"Wp_AXE_Move", new ST_PLAYER_AXE_MOVE));
	_States.insert(std::make_pair(L"Wp_AXE_Move_Left", new ST_PLAYER_AXE_MOVE_LEFT));
	_States.insert(std::make_pair(L"Wp_AXE_Move_Right", new ST_PLAYER_AXE_MOVE_RIGHT));
	_States.insert(std::make_pair(L"Wp_AXE_Move_Backward", new ST_PLAYER_AXE_MOVE_BACKWARD));
	_States.insert(std::make_pair(L"Wp_AXE_Move_Forward", new ST_PLAYER_AXE_MOVE_FORWARD));

	_States.insert(std::make_pair(L"Wp_AXE_HIT", new ST_PLAYER_WP_AXE_HIT));
	_States.insert(std::make_pair(L"Wp_AXE_HIT_F", new ST_PLAYER_WP_AXE_HIT_F));
	_States.insert(std::make_pair(L"Wp_AXE_HIT_L", new ST_PLAYER_WP_AXE_HIT_L));
	_States.insert(std::make_pair(L"Wp_AXE_HIT_B", new ST_PLAYER_WP_AXE_HIT_B));
	_States.insert(std::make_pair(L"Wp_AXE_HIT_R", new ST_PLAYER_WP_AXE_HIT_R));

	_States.insert(std::make_pair(L"Super_Bust_Attack", new ST_PLAYER_SUPER_BUST_ATTACK));
	_States.insert(std::make_pair(L"Bust_Attack", new ST_PLAYER_BUST_ATTACK));
	_States.insert(std::make_pair(L"Bust_Attack_Axe_Link", new ST_PLAYER_BUST_ATTACK_AXE_LINK));

	
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

void PlayerStateMachine::setCamera(CGameObject* camera)
{
	_Camera = camera;
}

void PlayerStateMachine::setSword(CGameObject* sword)
{
	_Sword = sword;
}
void PlayerStateMachine::setShield(CGameObject* shield)
{
	_Shield = shield;
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

AnimParamUnion PlayerStateMachine::GetASTMParam(std::wstring paramId)
{
	return _ASTM->GetParamByName(paramId)->value;
}

void PlayerStateMachine::OnAnimationBegin(IAnimationState* _pState)
{
	_curState->OnAnimationBegin(_pState,this);
}
void PlayerStateMachine::OnAnimationEndStart(IAnimationState* _pState)
{
	_curState->OnAnimationEndStart(_pState,this);
}
void PlayerStateMachine::OnAnimationEndFinished(IAnimationState* _pState)
{
	_curState->OnAnimationEndFinished(_pState,this);
}

CGameObject* PlayerStateMachine::GetCamera()
{
	return _Camera;
}

void PlayerStateMachine::ChangeScriptParam(std::wstring paramID, AnimParamType type, AnimParamUnion param)
{
		_Sword->GetScript<CSwordScript>()->SetASTMParam(paramID, type, param);
		_Shield->GetScript<CPlayerShieldScript>()->SetASTMParam(paramID, type, param);
}