#pragma once
#include "CComponent.h"
class CTransform;

class CBoneHolder :
	public CComponent
{
private:
	set<wstring>				m_setBoneNames;
	map<wstring, CTransform*>	m_mapBoneTransforms;
	bool						m_bIsSet;

public:
	void SetBoneName(set<wstring> _boneNames) { m_setBoneNames = _boneNames; m_bIsSet = false; m_mapBoneTransforms.clear(); }
	bool IsReady() { return m_bIsSet; }
	CTransform* GetBone(wstring _strBoneName);
	virtual void finaltick();

	CLONE(CBoneHolder);

public:
	virtual void SaveToLevelFile(FILE* _File);
	virtual void LoadFromLevelFile(FILE* _FILE);
public:
	CBoneHolder(set<wstring> _boneNames);
	CBoneHolder(const CBoneHolder& _other);
	~CBoneHolder();
};

