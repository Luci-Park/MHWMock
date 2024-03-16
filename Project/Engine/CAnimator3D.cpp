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
	, m_vecAnimNames(_origin.m_vecAnimNames)
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
}

Ptr<CAnimationClip> CAnimator3D::GetAnimation(wstring _key)
{
	auto iter = m_mapAnims.find(_key);
	if (iter != m_mapAnims.end())
		return iter->second;
	return nullptr;
}

void CAnimator3D::SetBool(wstring _param, bool _value)
{
	m_pAnimationStateMachine->SetBool(_param, _value);
}

void CAnimator3D::SetFloat(wstring _param, float _value)
{
	m_pAnimationStateMachine->SetFloat(_param, _value);
}

void CAnimator3D::SetInt(wstring _param, int _value)
{
	m_pAnimationStateMachine->SetInt(_param, _value);
}

void CAnimator3D::SetTrigger(wstring _param, bool _value)
{
	m_pAnimationStateMachine->SetTrigger(_param, _value);
}

void CAnimator3D::tick()
{
	if (!BoneHolder()->IsReady())return;
	m_pAnimationStateMachine->tick();
	vector<tAnimationKeyFrame> frame = m_pAnimationStateMachine->GetFrame();
	for (int i =0; i < frame.size(); i++)
	{
		auto pTransform = BoneHolder()->GetBone(frame[i].strBoneName);
		assert(pTransform);
		pTransform->SetRelativePos(frame[i].vPos);
		pTransform->SetRelativeRot(frame[i].qRot);
		pTransform->SetRelativeScale(frame[i].vScale);
	}


}

void CAnimator3D::finaltick()
{
#if DEBUG_ANIMATOR
	if (!BoneHolder()->IsReady())return;
	m_pAnimationStateMachine->tick();
	vector<tAnimationKeyFrame> frame = m_pAnimationStateMachine->GetFrame();
	for (int i = 0; i < frame.size(); i++)
	{
		auto pTransform = BoneHolder()->GetBone(frame[i].strBoneName);
		assert(pTransform);
		if (frame[i].strBoneName == L"Root")
		{
			Vec3 pos = Transform()->GetRelativePos() + frame[i].vPos;
			Quaternion rot = Transform()->GetRelativeRot() + frame[i].qRot;
			Transform()->SetRelativePos(pos);
			Transform()->SetRelativeRot(rot);
		}
		else
		{
			pTransform->SetRelativePos(frame[i].vPos);
			pTransform->SetRelativeRot(frame[i].qRot);
			pTransform->SetRelativeScale(frame[i].vScale);
		}
	}


	//매 틱마다 하는게 아닌 매 프레임 마다 움직이는 것
	//Root Motion
	//Root Bone을 받아옴
	//auto rootBone = BoneHolder()->GetBone(L"Root");
	//Transform()->SetRelativePos(Transform()->GetRelativePos() + rootBone->GetRelativePos());
	//Transform()->SetRelativeRot(Transform()->GetRelativeRot() + rootBone->GetRelativeRot());
	//rootBone->SetRelativePos(0, 0, 0);
	//rootBone->SetRelativeRot(0, 0, 0);
#endif
}


void CAnimator3D::SaveToLevelFile(FILE* _FILE)
{
	UINT count = m_mapAnims.size();
	fwrite(&count, sizeof(UINT), 1, _FILE);
	for (auto& clips : m_mapAnims)
		SaveResRef(clips.second.Get(), _FILE);
	m_pAnimationStateMachine->SaveToLevelFile(_FILE);
}

void CAnimator3D::LoadFromLevelFile(FILE* _FILE)
{
	UINT count;
	fread(&count, sizeof(UINT), 1, _FILE);
	for (int i = 0; i < count; i++)
	{
		Ptr<CAnimationClip> pAnim;
		LoadResRef(pAnim, _FILE);
		m_mapAnims.insert(make_pair(pAnim->GetKey(), pAnim));
		m_vecAnimNames.push_back(pAnim->GetKey());
	}
	m_pAnimationStateMachine->LoadFromLevelFile(_FILE);
}
