#pragma once
#include "CComponent.h"
class CTransform;

class CBoneHolder :
	public CComponent
{
private:
	vector<wstring> m_vecBoneNames;
	map<wstring, CTransform*> m_mapBoneTransforms;
	bool m_bIsSet;
public:
	void SetBoneName(vector<wstring> _boneNames) { m_vecBoneNames = _boneNames; m_bIsSet = false; m_mapBoneTransforms.clear(); }
	bool IsReady() { return m_bIsSet; }
	CTransform* GetBone(wstring _strBoneName);
	virtual void finaltick();
public:
	CBoneHolder();
	CBoneHolder(const CBoneHolder& _other);
	~CBoneHolder();
};

