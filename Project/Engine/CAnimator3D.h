#pragma once
#include "CComponent.h"
#define DEBUG_ANIMATOR 1
class CBoneHolder;
class CAnimationClip;
class CAnimationStateMachine;
class CAnimator3D :
	public CComponent
{
private:
	map<wstring, Ptr<CAnimationClip>>	m_mapAnims;
	vector<wstring>						m_vecAnimNames;
	CAnimationStateMachine*				m_pAnimationStateMachine;

	Vec3	curPos;
	Vec3	beforPos;

public:
	void SetAnimations(vector<wstring>& _vecAnimations);
	Ptr<CAnimationClip> GetAnimation(wstring _key);
	vector<wstring>& GetAnimNames() { return m_vecAnimNames; }
	CAnimationStateMachine* GetStateMachine() { return m_pAnimationStateMachine; }

	Ptr<CAnimationClip> GetCurrentAnimation(double& _percentage);

	void SetBool(wstring _param, bool _value);
	void SetFloat(wstring _param, float _value);
	void SetInt(wstring _param, int _value);
	void SetTrigger(wstring _param, bool _value = true);
public:
	virtual void tick() override;
	virtual void finaltick() override;

	void OnAnimationBegin(IAnimationState* _pState);
	void OnAnimationEndStart(IAnimationState* _pState);
	void OnAnimationEndFinished(IAnimationState* _pState);

	CLONE(CAnimator3D);

public:
	virtual void SaveToLevelFile(FILE* _FILE) override;
	virtual void LoadFromLevelFile(FILE* _FILE) override;

public:
	CAnimator3D();
	CAnimator3D(const CAnimator3D& _origin);
	~CAnimator3D();
};

