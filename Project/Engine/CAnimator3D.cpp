#include "pch.h"
#include "CAnimator3D.h"
#include "CAnimationClip.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CBoneHolder.h"
#include "ptr.h"


CAnimator3D::CAnimator3D()
	: CComponent(COMPONENT_TYPE::ANIMATOR3D)
{
}

CAnimator3D::CAnimator3D(const CAnimator3D& _origin)
	: CComponent(_origin)
	, m_mapAnims(_origin.m_mapAnims)
{
}

CAnimator3D::~CAnimator3D()
{
}

void CAnimator3D::SetAnimations(vector<wstring> _animations)
{
}

void CAnimator3D::SetAnimation(wstring _strAnim)
{
	if (m_mapAnims.contains(_strAnim))
	{
		m_pCurrAnim = m_mapAnims.find(_strAnim)->second;
	}
}

void CAnimator3D::finaltick()
{
	if (!m_bIsPlaying || m_pCurrAnim == nullptr) return;
	if (m_dTick >= m_pCurrAnim->GetDuration())
		m_dTick = 0;
	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * m_pCurrAnim->GetTicksPerSecond();//¿©±â¿¡ ºñÀ² °öÇÏ¸é µÊ.
	auto vecFrames = m_pCurrAnim->GetTransformsAtFrame(m_dTick);
	for (int i = 0; i < vecFrames.size(); i++)
	{
		auto pTransform = BoneHolder()->GetBone(vecFrames[i].strBoneName);
		pTransform->SetRelativePos(vecFrames[i].vPos);
		pTransform->SetRelativeRot(vecFrames[i].vRot);
		pTransform->SetRelativeScale(vecFrames[i].vScale);
	}
}

void CAnimator3D::SaveToLevelFile(FILE* _FILE)
{
	UINT count = m_mapAnims.size();
	fwrite(&count, sizeof(UINT), 1, _FILE);
	for (auto& clips : m_mapAnims)
		SaveResRef(clips.second.Get(), _FILE);
}

void CAnimator3D::LoadFromLevelFile(FILE* _FILE)
{
	UINT count;
	fread(&count, sizeof(UINT), 1, _FILE);
	for (int i = 0; i < count; i++)
	{
		Ptr<CAnimationClip> pAnim;
		LoadResRef(pAnim, _FILE);
	}
}
