#include "pch.h"
#include "CAnimationState.h"
#include "CAnimationTransition.h"
#include "CAnimationStateMachine.h"
#include "CTimeMgr.h"

CAnimationState::CAnimationState(CAnimationStateMachine* _pParent)
	: IAnimationState(eAnimationNodeType::State)
	, m_pClip(nullptr)
	, m_fSpeed(1)
	, m_dTick(0)
	, m_pMachine(_pParent)
	, m_iRepeatNum(0)
{
}

CAnimationState::CAnimationState(const CAnimationState& _other)
	: IAnimationState(eAnimationNodeType::State)
	, m_pClip(_other.m_pClip)
	, m_fSpeed(_other.m_fSpeed)
	, m_dTick(0)
	, m_pMachine(_other.m_pMachine)
	, m_iRepeatNum(0)
{
}

CAnimationState::~CAnimationState()
{
}

void CAnimationState::SetClip(Ptr<CAnimationClip> _pClip)
{
	m_pClip = _pClip;
	if (m_pClip != nullptr) m_FirstRootFrame = m_pClip->GetRootTransformAtFirstFrame("Root");
}

double CAnimationState::GetDurationInSeconds()
{
	if (m_pClip != nullptr)
		return m_pClip->GetDuration() / m_pClip->GetTicksPerSecond();
	return m_dDuration;
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

vector<tAnimationKeyFrame>& CAnimationState::GetBoneTransforms()
{
	m_vecKeyFrames.clear();
	if (m_pClip != nullptr)
	{
		m_vecKeyFrames = m_pClip->GetTransformsAtFrame(m_dTick);
		for (int i = 0; i < m_vecKeyFrames.size(); i++)
		{
			if (m_vecKeyFrames[i].strBoneName == L"Root")
			{
				if (m_bIsFirstTick)
				{
					m_prevRootFrame = m_FirstRootFrame;
					m_bIsFirstTick = false;
				}
				auto tempFrame = m_vecKeyFrames[i];
				m_vecKeyFrames[i].vPos -= m_prevRootFrame.vPos;

				Quaternion prevCon;
				m_prevRootFrame.qRot.Conjugate(prevCon);
				m_vecKeyFrames[i].qRot = prevCon * m_vecKeyFrames[i].qRot;

				m_prevRootFrame = tempFrame;
				break;
			}
		}
	}
	return m_vecKeyFrames;
}

void CAnimationState::Reset(double _percent, bool _repeat)
{
	SetTick(_percent);
	if (_repeat)m_iRepeatNum += 1;
	else m_iRepeatNum = 0;
	m_bIsFirstTick = true;
}

void CAnimationState::tick()
{
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
	fread(&m_fSpeed, sizeof(float), 1, _FILE);

	IAnimationState::LoadFromLevelFile(_FILE);
}
