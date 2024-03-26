#include "pch.h"
#include "CAnimator3D.h"
#include "CAnimationClip.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CBoneHolder.h"
#include "CAnimationStateMachine.h"
#include "CScript.h"

CAnimator3D::CAnimator3D()
	: CComponent(COMPONENT_TYPE::ANIMATOR3D)
{
	m_pAnimationStateMachine = new CAnimationStateMachine(this, nullptr, nullptr);
}

CAnimator3D::CAnimator3D(const CAnimator3D& _origin)
	: CComponent(_origin)
	, m_mapAnims(_origin.m_mapAnims)
	, m_vecAnimNames(_origin.m_vecAnimNames)
{
	m_pAnimationStateMachine = new CAnimationStateMachine(this, nullptr, nullptr);
	m_pAnimationStateMachine->SetName(L"Base Machine");
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

Ptr<CAnimationClip> CAnimator3D::GetCurrentAnimation(double& _percentage)
{
	_percentage = m_pAnimationStateMachine->GetTickPercent();
	return m_pAnimationStateMachine->GetClip();
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
	vector<tAnimationKeyFrame> frame = m_pAnimationStateMachine->GetBoneTransforms();
	for (int i = 0; i < frame.size(); i++)
	{
		auto pTransform = BoneHolder()->GetBone(frame[i].strBoneName);
		assert(pTransform);
		pTransform->SetRelativePos(frame[i].vPos);
		pTransform->SetRelativeRot(frame[i].qRot);
		pTransform->SetRelativeScale(frame[i].vScale);
	}

	auto rootBone = BoneHolder()->GetBone(L"Root");
	//assert(rootBone != nullptr);
	Vector3 rPos = rootBone->GetRelativePos();
	Vector3 pos = Transform()->GetRelativeDir(DIR_TYPE::RIGHT) * rPos.x
		+ Transform()->GetRelativeDir(DIR_TYPE::UP) * rPos.y
		+ Transform()->GetRelativeDir(DIR_TYPE::FRONT) * rPos.z;
	pos += Transform()->GetRelativePos();
	
	Vector3 rRot = rootBone->GetRelativeEulerRot();
	Vector3 rot = Transform()->GetRelativeDir(DIR_TYPE::RIGHT) * rRot.x
		+ Transform()->GetRelativeDir(DIR_TYPE::UP) * rRot.y
		+ Transform()->GetRelativeDir(DIR_TYPE::FRONT) * rRot.z;
	rot += Transform()->GetRelativeEulerRot();
	
	rootBone->SetRelativePos(0, 0, 0);
	rootBone->SetRelativeRot(0, 0, 0);
	Transform()->SetRelativePos(pos);                  
	Transform()->SetRelativeRot(rot);
}

void CAnimator3D::finaltick()
{
#if DEBUG_ANIMATOR
	tick();
#endif
}

void CAnimator3D::OnAnimationBegin(IAnimationState* _pState)
{
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnAnimationBegin(_pState);
	}
}

void CAnimator3D::OnAnimationEndStart(IAnimationState* _pState)
{
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnAnimationEndStart(_pState);
	}
}

void CAnimator3D::OnAnimationEndFinished(IAnimationState* _pState)
{
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnAnimationEndFinished(_pState);
	}
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
	while(count--)
	{
		Ptr<CAnimationClip> pAnim;
		LoadResRef(pAnim, _FILE);
		if (pAnim != nullptr)
		{
			m_mapAnims.insert(make_pair(pAnim->GetKey(), pAnim));
			m_vecAnimNames.push_back(pAnim->GetKey());
		}
	}
	m_pAnimationStateMachine->LoadFromLevelFile(_FILE);
	m_pAnimationStateMachine->SetName(L"Base Machine");
}
