#include "pch.h"
#include "CAnjanath.h"
#include <Engine/CAnimator3D.h>
#include "CMainPlayerScript.h"

CAnjanath::CAnjanath()
	: CScript(SCRIPT_TYPE::ANJANATH)
#pragma region Keys
	, aggroed(L"Aggroed")
	, turnDir(L"Turn Dir")
	, stopMove(L"Stop Move")
	, attackType(L"Attack Type")
	, hp(L"HP")
	, stagger(L"Stagger")
	, staggerType(L"Stagger Type")
	, rage(L"Rage")
	, rageNum(L"Rage Number")
	, m_iMaxHP(3528)
	, m_iMaxRage(370)
#pragma endregion
	, m_iHP(3528)
	, m_State(ANJ_STATE::PEACE)
	, m_iRageGauge(150)
	, m_iRageNumber(0)
	, m_bTailCut(false)
	, m_bMove(false)
{
	m_pAttackPicker = new AnjAttackPicker(this);
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pPlayer, "Player");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pNose1, "Nose1");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pNose2, "Nose2");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pWings, "Wing");
}

float Angles(const Vector3& v1, const Vector3& v2)
{
	float dot = v1.Dot(v2);
	float magprod = v1.Length() * v2.Length();
	if (magprod == 0.0) return 0.0;
	float cosAng = dot / magprod;
	float rad = acos(cosAng);
	return XMConvertToDegrees(rad);
}

CAnjanath::~CAnjanath()
{
	delete m_pAttackPicker;
}

void CAnjanath::Aggroed()
{
	Animator3D()->SetBool(aggroed, true);
	ANJ_MOVE_DIR dir;
	Vector3 front = Transform()->GetWorldDir(DIR_TYPE::FRONT) * -1;
	Vector3 playerDir = (m_pPlayer->Transform()->GetWorldPos() - Transform()->GetWorldPos()).Normalize();
	float angle = Angles(front, playerDir);
	if (angle <= 10)
		dir = ANJ_MOVE_DIR::FRONT;
	else if (angle <= 45)
		dir = ANJ_MOVE_DIR::SMALL_TURN;
	else if (front.Cross(playerDir).y > 0)//right
		dir = ANJ_MOVE_DIR::RIGHT;
	else
		dir = ANJ_MOVE_DIR::LEFT;

	Animator3D()->SetInt(turnDir, (int)dir);
}

void CAnjanath::begin()
{
	Animator3D()->SetBool(aggroed, false);
	Nose(false);
	Wing(false);
}

void CAnjanath::tick()
{
	Animator3D()->SetInt(hp, m_iHP);
	if (ANJ_STATE::PEACE == m_State) return;
	if (m_iHP <= 0) return;
	if (m_pCurrentAttack) m_pCurrentAttack->AttackTick(); // set dir, Move
	else LookAt();

}

void CAnjanath::ChooseAttack()
{
	if (m_iRageGauge <= 0)
	{
		EnRage();
		return;
	}
	LookAt();
	m_pCurrentAttack = m_pAttackPicker->PickAttack();
	m_pCurrentAttack->AttackStart();
	Animator3D()->SetInt(attackType, (int)m_pCurrentAttack->GetType());

}

void CAnjanath::EnRage()
{
	m_iRageGauge = m_iMaxRage;
	m_iRageNumber += 1;
	Animator3D()->SetTrigger(rage);
	Animator3D()->SetInt(rageNum, m_iRageNumber);
}

void CAnjanath::Death()
{
	Nose(false);
	Wing(false);
}

void CAnjanath::CheckWing(IAnimationState* _currentState, bool _start)
{
	const vector<wstring> startanims = { L"model\\anjanath\\anim\\Animation 001.004.anim", 
		L"model\\anjanath\\anim\\Animation 144.anim"};
	const vector<wstring> endanims = { L"model\\anjanath\\anim\\Animation 146.anim", };
	if (_start)
	{
		for (int i = 0; i < startanims.size(); i++)
		{
			if (_currentState->GetClip() == nullptr) continue;
			if (startanims[i] == _currentState->GetClip()->GetKey()) 
			{
				Wing(true);
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < endanims.size(); i++)
		{
			if (_currentState->GetClip() == nullptr) continue;
			if (endanims[i] == _currentState->GetClip()->GetKey())
			{
				Wing(false);
				break;
			}
		}
	}
}

void CAnjanath::CheckNose(IAnimationState* _currentState, bool _start)
{
	const vector<wstring> startanims = { L"model\\anjanath\\anim\\Animation 021.002.anim", };
	const vector<wstring> endanims = { };
	if (_start)
	{
		for (int i = 0; i < startanims.size(); i++)
		{
			if (_currentState->GetClip() == nullptr) continue;
			if (startanims[i] == _currentState->GetClip()->GetKey())
			{
				Nose(true);
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < endanims.size(); i++)
		{
			if (_currentState->GetClip() == nullptr) continue;
			if (endanims[i] == _currentState->GetClip()->GetKey())
			{
				Nose(false);
				break;
			}
		}
	}
}

void CAnjanath::LookAt()
{
	Matrix mat = Matrix::CreateLookAt(Transform()->GetWorldPos(), m_pPlayer->Transform()->GetWorldPos(), Transform()->GetWorldDir(DIR_TYPE::UP));
	Vector3 scale, pos; Quaternion rot;
	mat.Decompose(scale, rot, pos);
	Vector3 vRot = Transform()->GetRelativeEulerRot();
	vRot.y = rot.ToEuler().y;
	
	Transform()->SetRelativeRot(vRot);
}

void CAnjanath::StopAttack()
{
	if (m_pCurrentAttack)
	{
		m_pCurrentAttack->AttackEnd();
		m_pCurrentAttack = nullptr;
	}
}

void CAnjanath::Attacked(int _damage)
{
	if (ANJ_STATE::PEACE == m_State)
		Aggroed();
	m_iHP -= _damage;
	Animator3D()->SetInt(hp, m_iHP);
	if (m_iHP <= 0)
	{
		Death();
		return;
	}
	m_iRageGauge -= _damage;
}

void CAnjanath::AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player)
{
	if (!m_pCurrentAttack) return;
	m_pCurrentAttack->AttackSuccess(_type, _player);
}

void CAnjanath::NoseBreak()
{
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 0);
	Nose(false);
}

void CAnjanath::FallOver()
{
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 1);
}

void CAnjanath::TailCut()
{
	m_bTailCut = true;
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 1);
}

void CAnjanath::BodyShot()
{
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 0);
}

void CAnjanath::Nose(bool _show)
{
	m_pNose1->SetActive(_show);
	m_pNose2->SetActive(_show);
}

void CAnjanath::Wing(bool _show)
{
	m_pWings->SetActive(_show);
}

float CAnjanath::GetPlayerAngle()
{
	Vector3 front = Transform()->GetWorldDir(DIR_TYPE::FRONT) * -1;
	Vector3 playerDir = (m_pPlayer->Transform()->GetWorldPos() - Transform()->GetWorldPos()).Normalize();
	float angles = Angles(front, playerDir);
	if (front.Cross(playerDir).y > 0)//left
		angles *= -1;
	return angles;
}

float CAnjanath::GetPlayerDist()
{
	return Vec3::Distance(m_pPlayer->Transform()->GetWorldPos(), Transform()->GetWorldPos());
}

Vec3 CAnjanath::GetPlayerPos()
{
	return m_pPlayer->Transform()->GetWorldPos();
}

void CAnjanath::OnAnimationBegin(IAnimationState* _pState)
{
	CheckWing(_pState, true);
	CheckNose(_pState, true);

	if (_pState->GetType() == eAnimationNodeType::StateMachine && _pState->GetName() == L"Attack")	ChooseAttack();
	if (_pState->GetType() == eAnimationNodeType::State && _pState->GetName() == L"Move")	m_bMove = true;
	if (_pState->GetType() == eAnimationNodeType::State && _pState->GetName() == L"Rotate Time") LookAt();
}

void CAnjanath::OnAnimationEndStart(IAnimationState* _pState)
{
	CheckWing(_pState, false);
	CheckNose(_pState, false);
	if (_pState->GetType() == eAnimationNodeType::StateMachine && _pState->GetName() == L"Attack")StopAttack();
	if (_pState->GetType() == eAnimationNodeType::State && _pState->GetName() == L"Move")	m_bMove = false;
}

void CAnjanath::OnAnimationEndFinished(IAnimationState* _pState)
{
}

void CAnjanath::SaveToLevelFile(FILE* _File)
{
	SaveGameObjectParam(m_pPlayer, _File);
	SaveGameObjectParam(m_pNose1, _File);
	SaveGameObjectParam(m_pNose2, _File);
	SaveGameObjectParam(m_pWings, _File);
}

void CAnjanath::LoadFromLevelFile(FILE* _File)
{
	LoadGameObjectParam(0, _File);
	LoadGameObjectParam(1, _File);
	LoadGameObjectParam(2, _File);
	LoadGameObjectParam(3, _File);
}
