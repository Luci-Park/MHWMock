#include "pch.h"
#include "CAnimationState.h"
#include "CAnimationTransition.h"
#include "CTimeMgr.h"


CAnimationState::CAnimationState()
	: m_strName(L"New State")
	, m_vecTransitions()
	, m_pClip(nullptr)
	, m_fSpeed(1)
	, m_dTick(0)
{
}

CAnimationState::CAnimationState(const CAnimationState& _other)
	: m_strName(L"New State")
	, m_vecTransitions()
	, m_pClip(_other.m_pClip)
	, m_fSpeed(_other.m_fSpeed)
	, m_dTick(0)
{
}

CAnimationState::~CAnimationState()
{
}

vector<tAnimationKeyFrame>& CAnimationState::GetBoneTransforms()
{
	vector<tAnimationKeyFrame> vecEmpty;
	if (m_pClip == nullptr)
		return vecEmpty;
	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * m_pClip->GetTicksPerSecond() * m_fSpeed;
	return m_pClip->GetTransformsAtFrame(m_dTick);
}
