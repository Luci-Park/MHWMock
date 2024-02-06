#include "pch.h"
#include "CAnimationState.h"

#pragma region State
CAnimationState::CAnimationState()
	: m_strName(L"New State")
	, m_vecTransitions()
	, m_pClip(nullptr)
	, m_fSpeed(1)
{
}

CAnimationState::CAnimationState(const CAnimationState& _other)
	: m_strName(L"New State")
	, m_vecTransitions()
	, m_pClip(_other.m_pClip)
	, m_fSpeed(_other.m_fSpeed)
{
}

CAnimationState::~CAnimationState()
{
}
#pragma endregion

#pragma region Transition
CAnimationTransition::CAnimationTransition()
{
}

CAnimationTransition::CAnimationTransition(const CAnimationTransition& _other)
{
}

CAnimationTransition::~CAnimationTransition()
{
}
#pragma endregion
