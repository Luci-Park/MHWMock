#include "pch.h"
#include "CAnimationTransition.h"
#include "CAnimationState.h"

CAnimationTransition::CAnimationTransition()
	: m_pPrevState(nullptr)
	, m_pNextState(nullptr)
{
}

CAnimationTransition::~CAnimationTransition()
{
}