#include "pch.h"
#include "CPlayerShieldScript.h"
#include <Engine/CTransform.h>
#include "CAnjanathPart.h"

CPlayerShieldScript::CPlayerShieldScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSHIELDSCRIPT)
	, m_eHandDir(HandDir::None)
	, _ASTM(nullptr)
	, m_pPlayer(nullptr)
	, m_pLeftBone(nullptr)
	, m_pRightBone(nullptr)
	, m_pBackBone(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pPlayer, "Player");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pLeftBone, "Left Bone");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pRightBone, "Right Bone");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pBackBone, "Back Bone");
}

CPlayerShieldScript::~CPlayerShieldScript()
{
}

void CPlayerShieldScript::begin()
{
	_ASTM = GetOwner()->Animator3D()->GetStateMachine();


}

void CPlayerShieldScript::tick()
{
	if (m_eHandDir == HandDir::None && m_pBackBone != nullptr)
	{
		m_eHandDir = HandDir::Back;
		GetOwner()->SetParent(m_pBackBone);

		GetOwner()->Transform()->SetRelativePos(Vector3(0.f, -20.f, 20.f));
		GetOwner()->Transform()->SetRelativeScale(Vector3(0.008f, 0.008f, 0.008f));
		GetOwner()->Transform()->SetRelativeRot(Vector3(0.f, 180.f, 0.f));
	}

	if (!GetASTMParam(L"Wp_On").BOOL)
	{
		if (m_eHandDir == HandDir::Back)
		{
		}
		else
		{
			ChangeParent(HandDir::Back);
		}
	}
	else
	{
		if (GetASTMParam(L"IsAxe").BOOL || GetASTMParam(L"Bust_Attack").BOOL 
			|| GetASTMParam(L"Super_Bust_Attack").BOOL || GetASTMParam(L"Bottle_Charge").BOOL
			|| _ASTM->GetCurrentState()->GetName() == L"Wp_Bottle_Charge_S" 
			|| _ASTM->GetCurrentState()->GetName() == L"Wp_Bottle_Charge_F" 
			|| _ASTM->GetCurrentState()->GetName() == L"Wp_Enchent_K")
		{
			if (m_eHandDir == HandDir::Left)
			{
			}
			else
			{
				ChangeParent(HandDir::Left);
			}
		}
		else
		{
			if (m_eHandDir == HandDir::Right)
			{
			}
			else
			{
				ChangeParent(HandDir::Right);
			}
		}
	}

}

void CPlayerShieldScript::OnCollisionEnter(CCollider3D* _Other)
{
	CAnjanathPart* coll = _Other->GetOwner()->GetScript<CAnjanathPart>();
	if (coll != nullptr && m_IsAttack == true)
	{
		coll->Attacked(10);
		m_IsAttack = false;
	}
}

void CPlayerShieldScript::OnCollisionStay(CCollider3D* _Other)
{
}

void CPlayerShieldScript::OnCollisionExit(CCollider3D* _Other)
{
}

void CPlayerShieldScript::OnTriggerEnter(CCollider3D* _Other)
{
}

void CPlayerShieldScript::OnTriggerExit(CCollider3D* _Other)
{
}

void CPlayerShieldScript::ChangeParent(HandDir _HandDir)
{
	if (m_pLeftBone == nullptr || m_pRightBone == nullptr || m_pBackBone == nullptr)
		return;

	if (_HandDir == HandDir::Left)
	{
		m_eHandDir = HandDir::Left;
		GetOwner()->SetParent(m_pLeftBone);

		GetOwner()->Transform()->SetRelativePos(Vector3(0.f, 0.f, 0.f));
		GetOwner()->Transform()->SetRelativeScale(Vector3(0.008f, 0.008f, 0.008f));
		GetOwner()->Transform()->SetRelativeRot(Vector3(270.f, 0.f, 0.f));
	}
	else if(_HandDir == HandDir::Right)
	{
		m_eHandDir = HandDir::Right;
		GetOwner()->SetParent(m_pRightBone);

		GetOwner()->Transform()->SetRelativePos(Vector3(0.f, 0.f, 0.f));
		GetOwner()->Transform()->SetRelativeScale(Vector3(0.008f, 0.008f, 0.008f));
		GetOwner()->Transform()->SetRelativeRot(Vector3(270.f, 90.f, 0.f));
	}
	else if (_HandDir == HandDir::Back)
	{
		m_eHandDir = HandDir::Back;
		GetOwner()->SetParent(m_pBackBone);

		GetOwner()->Transform()->SetRelativePos(Vector3(0.f, -20.f, 20.f));
		GetOwner()->Transform()->SetRelativeScale(Vector3(0.008f, 0.008f, 0.008f));
		GetOwner()->Transform()->SetRelativeRot(Vector3(0.f, 180.f, 0.f));
	}
}

void CPlayerShieldScript::SetASTMParam(std::wstring paramID, AnimParamType type, AnimParamUnion param)
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

AnimParamUnion CPlayerShieldScript::GetASTMParam(std::wstring paramID)
{
	return _ASTM->GetParamByName(paramID)->value;
}

void CPlayerShieldScript::IsAttack(bool isattack)
{

}

