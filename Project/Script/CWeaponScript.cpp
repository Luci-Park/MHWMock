#include "CWeaponScript.h"


CWeaponScript::CWeaponScript()
	: CScript((UINT)SCRIPT_TYPE::WEAPONSCRIPT)
	, _ASTM(nullptr)
	, _Player(nullptr)
	, _MainBone(nullptr)
	, _SubBone(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_Player, "Player");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_MainBone, "Main Bone");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_SubBone, "Sub Bone");
}

CWeaponScript::~CWeaponScript()
{
}


void CWeaponScript::begin()
{
	_ASTM = GetOwner()->Animator3D()->GetStateMachine();
}

void CWeaponScript::SetASTMParam(std::wstring paramID, AnimParamType type, AnimParamUnion param)
{
	switch (type)
	{
	case AnimParamType::FLOAT:
		_ASTM->SetFloat(paramID, param.FLOAT);
		break;
	case AnimParamType::INT:
		_ASTM->SetInt(paramID, param.INT);
		break;
	case AnimParamType::BOOL:
		_ASTM->SetBool(paramID, param.BOOL);
		break;
	case AnimParamType::TRIGGER:
		_ASTM->SetTrigger(paramID, param.TRIGGER);
		break;
	default:
		break;
	}
}

AnimParamUnion CWeaponScript::GetASTMParam(std::wstring paramID)
{
	return _ASTM->GetParamByName(paramID)->value;
}
