#pragma once
#include "CComponent.h"
class CAnimationClip;
class CAnimator3D :
	public CComponent
{
private:
	map<wstring, Ptr<CAnimationClip>>	m_mapAnims;
	Ptr<CAnimationClip>					m_CurrAnim;
	vector<tAnimationKeyFrame>		m_vecCurrentFrames;

	int m_tick;
	bool m_bIsPlaying;
public:
	void SetAnimations(vector<wstring> _animations);
	void SetAnimation(wstring _strAnim);
public:
	virtual void finaltick() override;
	CLONE(CAnimator3D);

public:
	virtual void SaveToLevelFile(FILE* _FILE) override;
	virtual void LoadFromLevelFile(FILE* _FILE) override;

public:
	CAnimator3D();
	CAnimator3D(const CAnimator3D& _origin);
	~CAnimator3D();
};

