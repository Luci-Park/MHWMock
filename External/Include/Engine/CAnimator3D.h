#pragma once
#include "CComponent.h"
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

public:
	void SetAnimations(vector<wstring>& _vecAnimations);
	Ptr<CAnimationClip> GetAnimation(wstring _key);
	vector<wstring>& GetAnimNames() { return m_vecAnimNames; }
	CAnimationStateMachine* GetStateMachine() { return m_pAnimationStateMachine; }

	void SetBool(wstring _param, bool _value);
	void SetFloat(wstring _param, float _value);
	void SetInt(wstring _param, int _value);
	void SetTrigger(wstring _param, bool _value = true);
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

