#include "pch.h"
#include "CAnimator3D.h"
#include "CAnimationClip.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CBoneHolder.h"
#include "CAnimationStateMachine.h"

CAnimator3D::CAnimator3D()
	: CComponent(COMPONENT_TYPE::ANIMATOR3D)
{
	m_pAnimationStateMachine = new CAnimationStateMachine(this);
}

CAnimator3D::CAnimator3D(const CAnimator3D& _origin)
	: CComponent(_origin)
	, m_mapAnims(_origin.m_mapAnims)
{
	m_pAnimationStateMachine = new CAnimationStateMachine(this);
}

CAnimator3D::~CAnimator3D()
{
	if (m_pAnimationStateMachine)
		delete m_pAnimationStateMachine;
}

void CAnimator3D::SetAnimations(vector<wstring>& _vecAnimations)
{
	m_mapAnims.clear();
	m_vecAnimNames.clear();
	for (int i = 0; i < _vecAnimations.size(); i++)
	{
		Ptr<CAnimationClip> pAnim = CResMgr::GetInst()->FindRes<CAnimationClip>(_vecAnimations[i]);
		m_mapAnims.insert(make_pair(_vecAnimations[i], pAnim));
		m_vecAnimNames.push_back(_vecAnimations[i]);
	}
	m_pCurrAnim = CResMgr::GetInst()->FindRes<CAnimationClip>(_vecAnimations[0]);
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
	if (!BoneHolder()->IsReady())return;
	map<wstring, tAnimationKeyFrame> frame = m_pAnimationStateMachine->GetFrame();
	for (auto f : frame)
	{
		auto pTransform = BoneHolder()->GetBone(f.first);
		assert(pTransform);
		pTransform->SetRelativePos(f.second.vPos);
		pTransform->SetRelativeRot(f.second.qRot);
		pTransform->SetRelativeScale(f.second.vScale);
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
