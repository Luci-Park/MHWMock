#pragma once
#include "CComponent.h"
class CBoneHolder;
class CAnimationClip;
class CAnimator3D :
	public CComponent
{
private:
	map<wstring, Ptr<CAnimationClip>>	m_mapAnims;
	vector<wstring>						m_vecAnimNames;
	Ptr<CAnimationClip>					m_pCurrAnim;

	double								m_dTick;
	bool								m_bIsPlaying;
public:
	void SetAnimations(vector<wstring>& _vecAnimations);
	void SetAnimation(wstring _strAnim);
	vector<wstring> GetAnimNames() { return m_vecAnimNames; }

	void PlayAnimation() { m_bIsPlaying = true; }
	void PauseAnimation() { m_bIsPlaying = false; }
	void StopAnimation() { m_bIsPlaying = false; m_dTick = 0; }
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

