#include "pch.h"
#include "CAnimationTransition.h"
#include "CAnimationStateMachine.h"
#include "CAnimationState.h"
#include "CTimeMgr.h"


CAnimationTransition::CAnimationTransition(CAnimationState* _pPrevState, CAnimationState* _pNextState, CAnimationStateMachine* _pMachine)
	: m_pStateMachine(_pMachine)
	, m_pPrevState(_pPrevState)
	, m_pNextState(_pNextState)
	, m_bHasExitTime(true)
	, m_dExitTime(1)
	, m_bFixedDuration(false)
	, m_dTransitionDuration(0.25)
	, m_dTransitionOffset(0)
{
}

CAnimationTransition::~CAnimationTransition()
{
	for (int i = 0; i < m_vecConditions.size(); i++)
	{
		delete m_vecConditions[i];
	}
}

map<wstring, tAnimationKeyFrame>& CAnimationTransition::GetTransitionKeyFrame()
{
	m_mapKeyFrame.clear();
	BlendKeyFrame(m_pPrevState->GetBoneTransforms(), true);
	BlendKeyFrame(m_pNextState->GetBoneTransforms(), false);

	return m_mapKeyFrame;
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
	if (m_bHasExitTime && m_pPrevState->GetTickPercent() < m_dExitTime)
		return false;
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
}

void CAnimationTransition::Remove()
{
	m_pPrevState->DeleteTransition(this);
}

void CAnimationTransition::finaltick()
{
	double offset = 1;
	if (!m_bFixedDuration)
	{
		offset = m_pPrevState->GetClip()->GetTicksPerSecond()
			* m_pPrevState->GetSpeed();
	}
	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * offset;

	if (m_bFixedDuration)
		m_dTickPercent = m_dTick / m_dTransitionDuration;
	else
		m_dTickPercent = m_dTick / m_pPrevState->GetClip()->GetDuration();

	if (m_dTickPercent >= 1)
		EndTransition();
		
}

void CAnimationTransition::EndTransition()
{
	m_pStateMachine->ChangeState(m_pNextState);
	m_pPrevState->OnTransitionEnd();
}

void CAnimationTransition::BlendKeyFrame(vector<tAnimationKeyFrame>& frames, bool minus)
{
	double percent = minus ? 1 - m_dTickPercent : m_dTickPercent;
	for (int i = 0; i < frames.size(); i++)
	{
		tAnimationKeyFrame newFrame = frames[i] * percent;
		auto iter = m_mapKeyFrame.find(frames[i].strBoneName);
		if (iter == m_mapKeyFrame.end())
		{
			m_mapKeyFrame.insert(make_pair(frames[i].strBoneName, newFrame));
		}
		else
		{
			iter->second += newFrame;
		}
	}
}
