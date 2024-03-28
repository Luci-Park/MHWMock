#include "pch.h"
#include "CAnimationTransition.h"
#include "CAnimationStateMachine.h"
#include "CAnimationState.h"
#include "CTimeMgr.h"
#include "CAnimator3D.h"

CAnimationTransition::CAnimationTransition(IAnimationState* _pPrevState, IAnimationState* _pNextState, CAnimationStateMachine* _pMachine)
	: m_pStateMachine(_pMachine)
	, m_pPrevState(_pPrevState)
	, m_pNextState(_pNextState)
	, m_bHasExitTime(true)
	, m_dExitTime(0.75)
	, m_bFixedDuration(false)
	, m_dTransitionDuration(0.25)
	, m_dTransitionOffset(0)
{
	m_pPrevState->AddTransition(this);
}

CAnimationTransition::~CAnimationTransition()
{
	for (int i = 0; i < m_vecConditions.size(); i++)
	{
		delete m_vecConditions[i];
	}
}

KeyFrames& CAnimationTransition::GetTransitionKeyFrame()
{
	m_rsltKeyFrames.clear();
	BlendKeyFrames(m_pPrevState->GetBoneTransforms(), m_pNextState->GetBoneTransforms(), m_dTickPercent);

	return m_rsltKeyFrames;
}

AnimCondition* CAnimationTransition::CreateCondition()
{
	auto param = m_pStateMachine->GetParamByIndex(0);
	if(param == nullptr) return nullptr;

	m_vecConditions.push_back(new AnimCondition(param));
	return m_vecConditions.back();
}

void CAnimationTransition::DeleteCondition(int _idx)
{
	if(0 <= _idx && _idx < m_vecConditions.size())
		m_vecConditions.erase(m_vecConditions.begin() + _idx);
}

void CAnimationTransition::DeleteCondition(AnimCondition* _condition)
{
	for (int i = 0; i < m_vecConditions.size(); i++)
	{
		if (m_vecConditions[i] == _condition)
		{
			m_vecConditions.erase(m_vecConditions.begin() + i);
			return;
		}
	}
}

bool CAnimationTransition::CheckCondition()
{
	if (m_bHasExitTime)
	{
		if(eAnimationNodeType::State == m_pPrevState->GetType() 
			&& m_pPrevState->GetTickPercentWithRepeat() < m_dExitTime)
			return false;
		else if (eAnimationNodeType::StateMachine == m_pPrevState->GetType())
		{
			auto sm = (CAnimationStateMachine*)m_pPrevState;
			if (sm->GetCurrentState() != sm->GetTail())
				return false;
		}
	}
	for (int i = 0; i < m_vecConditions.size(); i++)
	{
		AnimCondition* c = m_vecConditions[i];
		if (AnimParamType::TRIGGER == c->lhs->type)
		{
			if(!c->lhs->value.TRIGGER)
				return false;
		}
		else if (AnimParamType::BOOL == c->lhs->type)
		{
			if ((c->expr == AnimConditionType::ISTRUE && !c->lhs->value.BOOL)
				|| (c->expr == AnimConditionType::ISFALSE && c->lhs->value.BOOL))
				return false;
		}
		else if (AnimParamType::INT == c->lhs->type)
		{
			int value = (int)c->rhs;
			if ((c->expr == AnimConditionType::GREATER && c->lhs->value.INT <= value)
				|| (c->expr == AnimConditionType::LESS && c->lhs->value.INT >= value)
				|| (c->expr == AnimConditionType::EQUAL && c->lhs->value.INT != value)
				|| (c->expr == AnimConditionType::NOTEQUAL && c->lhs->value.INT == value))
				return false;
		}
		else if (AnimParamType::FLOAT == c->lhs->type)
		{
			if ((c->expr == AnimConditionType::GREATER && c->lhs->value.FLOAT < c->rhs)
				|| (c->expr == AnimConditionType::LESS && c->lhs->value.FLOAT > c->rhs))
				return false;

		}
	}
	//reset used triggers
	for (int i = 0; i < m_vecConditions.size(); i++)
	{
		AnimCondition* c = m_vecConditions[i];
		if (AnimParamType::TRIGGER == c->lhs->type)
			c->lhs->value.TRIGGER = false;
	}
	return true;
}

void CAnimationTransition::StartTransition()
{
	m_dTick = 0;
	m_pNextState->OnTransitionBegin(m_dTransitionOffset);
	auto animator = m_pPrevState->GetAnimator();
	animator->OnAnimationEndStart(m_pPrevState);
	animator->OnAnimationBegin(m_pNextState);
}

void CAnimationTransition::ChangeConditionParam(AnimCondition* _cond, AnimStateParam* _param)
{
	if (_cond->lhs->type != _param->type)
	{
		if (AnimParamType::FLOAT == _param->type
			|| AnimParamType::INT == _param->type)
			_cond->expr = AnimConditionType::GREATER;
		if (AnimParamType::BOOL == _param->type
			|| AnimParamType::TRIGGER == _param->type)
			_cond->expr = AnimConditionType::ISTRUE;
	}
	_cond->lhs = _param;
}

void CAnimationTransition::Remove()
{
	m_pPrevState->DeleteTransition(this);
}

void CAnimationTransition::tick()
{
	double duration = m_bFixedDuration ? m_dTransitionDuration : m_pPrevState->GetDurationInSeconds() * m_dTransitionDuration;
	m_dTick += CTimeMgr::GetInst()->GetDeltaTime();
	m_dTickPercent = m_dTick / duration;

	if (m_dTickPercent >= 1)
		EndTransition();
		
}

void CAnimationTransition::EndTransition()
{
	m_pStateMachine->ChangeState(m_pNextState);
	m_pPrevState->OnTransitionEnd();
	m_pPrevState->GetAnimator()->OnAnimationEndFinished(m_pPrevState);
}

void CAnimationTransition::BlendKeyFrames(KeyFrames& _prevFrames, KeyFrames& _nextFrames, float _ratio)
{
	m_rsltKeyFrames.clear();
	for (auto frames : _prevFrames)
		m_rsltKeyFrames.emplace(frames.first, frames.second);

	for (auto frames : _nextFrames)
	{
		auto prev = m_rsltKeyFrames.find(frames.first);
		if (prev == m_rsltKeyFrames.end())
		{
			m_rsltKeyFrames.emplace(frames.first, frames.second);
		}
		else
		{
			prev->second.vPos = Vec3::Lerp(prev->second.vPos, frames.second.vPos, _ratio);
			prev->second.qRot = Quaternion::Lerp(prev->second.qRot, frames.second.qRot, _ratio);
			prev->second.vScale = Vec3::Lerp(prev->second.vScale, frames.second.vScale, _ratio);
		}
	}
}

void CAnimationTransition::SaveToLevelFile(FILE* _FILE)
{
	fwrite(&m_bHasExitTime, sizeof(bool), 1, _FILE);
	fwrite(&m_dExitTime, sizeof(double), 1, _FILE);
	fwrite(&m_bFixedDuration, sizeof(bool), 1, _FILE);
	fwrite(&m_dTransitionDuration, sizeof(double), 1, _FILE);
	fwrite(&m_dTransitionOffset, sizeof(double), 1, _FILE);

	int count = m_vecConditions.size();
	fwrite(&count, sizeof(int), 1, _FILE);
	for (size_t i = 0; i < count; i++)
	{
		auto cond = m_vecConditions[i];
		SaveWString(cond->lhs->name, _FILE);
		int expr = (int)cond->expr;
		fwrite(&expr, sizeof(int), 1, _FILE);
		fwrite(&cond->rhs, sizeof(float), 1, _FILE);
	}
	fwrite(&m_tLinkInfo, sizeof(tAnimationTransitionLink), 1, _FILE);
}

void CAnimationTransition::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_bHasExitTime, sizeof(bool), 1, _FILE);
	fread(&m_dExitTime, sizeof(double), 1, _FILE);
	fread(&m_bFixedDuration, sizeof(bool), 1, _FILE);
	fread(&m_dTransitionDuration, sizeof(double), 1, _FILE);
	fread(&m_dTransitionOffset, sizeof(double), 1, _FILE);

	int count;
	fread(&count, sizeof(int), 1, _FILE);
	m_vecConditions.resize(count);
	for (size_t i = 0; i < count; i++)
	{
		wstring paramName; LoadWString(paramName, _FILE);
		AnimStateParam* param = m_pStateMachine->GetParamByName(paramName);

		AnimCondition* newCond = new AnimCondition(param);
		int type = 0; fread(&type, sizeof(int), 1, _FILE);
		newCond->expr = (AnimConditionType)type;
		fread(&newCond->rhs, sizeof(float), 1, _FILE);
		m_vecConditions[i] = newCond;
	}

	fread(&m_tLinkInfo, sizeof(tAnimationTransitionLink), 1, _FILE);
}
