#include "pch.h"
#include "CAnimator3D.h"
#include "CAnimationClip.h"
#include "CResMgr.h"
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
		m_CurrAnim = m_mapAnims.find(_strAnim)->second;
}

void CAnimator3D::finaltick()
{
	if(m_tick < )
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
