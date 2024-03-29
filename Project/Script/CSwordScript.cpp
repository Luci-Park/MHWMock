#include "pch.h"
#include "CSwordScript.h"

CSwordScript::CSwordScript()
	: CScript((UINT)SCRIPT_TYPE::SWORDSCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_Player, "Player");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_MainBone, "Main Bone");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &_SubBone, "Sub Bone");
}

CSwordScript::~CSwordScript()
{
}

void CSwordScript::begin()
{
	_ASTM = GetOwner()->Animator3D()->GetStateMachine();
	if (_SubBone != nullptr)
		SetSubBone();
}

void CSwordScript::tick()
{
}

void CSwordScript::OnCollisionEnter(CCollider3D* _Other)
{
}

void CSwordScript::OnCollisionStay(CCollider3D* _Other)
{
}

void CSwordScript::OnCollisionExit(CCollider3D* _Other)
{
}

void CSwordScript::OnTriggerEnter(CCollider3D* _Other)
{
}

void CSwordScript::OnTriggerExit(CCollider3D* _Other)
{
}

void CSwordScript::OnAnimationBegin(IAnimationState* _pState)
{
}

void CSwordScript::OnAnimationEndStart(IAnimationState* _pState)
{
}

void CSwordScript::OnAnimationEndFinished(IAnimationState* _pState)
{
}

void CSwordScript::SaveToLevelFile(FILE* _File)
{
}

void CSwordScript::LoadFromLevelFile(FILE* _FILE)
{
	begin();
}

void CSwordScript::SetASTMParam(std::wstring paramID, AnimParamType type, AnimParamUnion param)
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

AnimParamUnion CSwordScript::GetASTMParam(std::wstring paramID)
{
	return _ASTM->GetParamByName(paramID)->value;
}

void CSwordScript::SetMainBone()
{
	GetOwner()->SetParent(_MainBone);
}

void CSwordScript::SetSubBone()
{
	GetOwner()->SetParent(_SubBone);
	GetOwner()->Transform()->SetRelativePos(Vec3(0.f, 20.f, 30.f));
	GetOwner()->Transform()->SetRelativeRot(Vec3(180.f, 0.f, 0.f));
	GetOwner()->Transform()->SetRelativeScale(Vec3(0.005f, 0.005f, 0.005f));
}
