#include "pch.h"
#include "CAnimationState.h"
#include "CAnimationTransition.h"
#include "CAnimationStateMachine.h"
#include "CTimeMgr.h"

CAnimationState::CAnimationState(CAnimator3D* _animator3D, CAnimationStateMachine* _root, CAnimationStateMachine* _parent)
	: IAnimationState(eAnimationNodeType::State, _animator3D, _root, _parent)
	, m_pClip(nullptr)
	, m_fSpeed(1)
	, m_dTick(0)
	, m_iRepeatNum(0)
{
}

CAnimationState::CAnimationState(const CAnimationState& _other)
	: IAnimationState(eAnimationNodeType::State, _other.m_pAnimator, _other.m_pRootMachine, _other.m_pParentMachine)
	, m_pClip(_other.m_pClip)
	, m_fSpeed(_other.m_fSpeed)
	, m_dTick(0)
	, m_iRepeatNum(0)
{
}

CAnimationState::~CAnimationState()
{
}

void CAnimationState::SetClip(Ptr<CAnimationClip> _pClip)
{
	m_pClip = _pClip;
	Reset(0, false);
}

double CAnimationState::GetDurationInSeconds()
{
	if (m_pClip != nullptr)
		return m_pClip->GetDuration() / m_pClip->GetTicksPerSecond() / m_fSpeed;
	return m_dDuration / m_fSpeed;
}
void CAnimationState::SetTick(double _percent)
{
	m_dDuration = m_pClip != nullptr ? m_pClip->GetDuration() : 1;
	m_dTick = m_dDuration * _percent;
}

double CAnimationState::GetTickPercent()
{
	return abs(m_dTick / m_dDuration);
}

double CAnimationState::GetTickPercentWithRepeat()
{
	float duration = m_dTick + m_dDuration * m_iRepeatNum;
	return abs(duration / m_dDuration);
}

void CAnimationState::OnTransitionEnd()
{
	IAnimationState::OnTransitionEnd();
	m_dTick = 0;
}

void CAnimationState::OnTransitionBegin(double _tickPercent)
{
	Reset(_tickPercent, false);
}

KeyFrames& CAnimationState::GetBoneTransforms()
{
	m_bTicked = false;

	static KeyFrames emptyFrames(0);
	if (m_pClip == nullptr) return emptyFrames;

	KeyFrames& frames = m_pClip->GetTransformsAtFrame(m_dTick);
	auto rootKey = frames.find(L"Root");
	if (rootKey != frames.end())
	{
		auto tempFrame = rootKey->second;
		if (m_bIsFirstTick)
		{
			m_prevRootFrame = tempFrame;
			m_bIsFirstTick = false;
		}
		rootKey->second.vPos -= m_prevRootFrame.vPos;

		Quaternion prevCon;
		m_prevRootFrame.qRot.Conjugate(prevCon);
		rootKey->second.qRot = prevCon * rootKey->second.qRot;

		m_prevRootFrame = tempFrame;
	}
	return frames;
	
}

void CAnimationState::Reset(double _percent, bool _addToRepeat)
{
	m_bTicked = false;

	SetTick(_percent);
	if (_addToRepeat)m_iRepeatNum += 1;
	else m_iRepeatNum = 0;
	m_bIsFirstTick = true;
}

void CAnimationState::tick()
{
	if (m_bTicked) return;
	m_bTicked = true;

	m_dDuration = m_pClip != nullptr ? m_pClip->GetDuration() : 1;
	double offset = m_pClip != nullptr ? m_pClip->GetTicksPerSecond() : 1;

	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * offset * m_fSpeed;
	if (m_dTick > m_dDuration) Reset(0, true);
	if (m_dTick < 0) Reset(m_dDuration, true);

	IAnimationState::tick();
}

void CAnimationState::SaveToLevelFile(FILE* _FILE)
{
	SaveResRef(m_pClip.Get(), _FILE);
	fwrite(&m_fSpeed, sizeof(float), 1, _FILE);

	IAnimationState::SaveToLevelFile(_FILE);
}

void CAnimationState::LoadFromLevelFile(FILE* _FILE)
{
	LoadResRef(m_pClip, _FILE);
	SetClip(m_pClip);
	fread(&m_fSpeed, sizeof(float), 1, _FILE);

	IAnimationState::LoadFromLevelFile(_FILE);
}
