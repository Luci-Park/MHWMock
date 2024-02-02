#include "pch.h"
#include "CBoneHolder.h"
#include "CTransform.h"


CBoneHolder::CBoneHolder(vector<wstring> _boneNames)
	: CComponent(COMPONENT_TYPE::BONEHOLDER)
	, m_bIsSet(false)
	, m_vecBoneNames(_boneNames)
{
}

CBoneHolder::CBoneHolder(const CBoneHolder& _other)
	: CComponent(_other)
	, m_vecBoneNames(_other.m_vecBoneNames)
	, m_bIsSet(false)
{
}

CBoneHolder::~CBoneHolder()
{
}

CTransform* CBoneHolder::GetBone(wstring _strBoneName)
{
	if(!m_bIsSet)
		return nullptr;
	auto pRslt = m_mapBoneTransforms.find(_strBoneName);
	if (pRslt == m_mapBoneTransforms.end())
		return nullptr;
	return pRslt->second;
}

void CBoneHolder::finaltick()
{
	if (m_bIsSet) return;
	for (int i = 0; i < m_vecBoneNames.size(); i++)
	{
		auto node = m_mapBoneTransforms.find(m_vecBoneNames[i]);
		if (node == m_mapBoneTransforms.end())
		{
			CGameObject* pNode = GetOwner()->FindChildByName(m_vecBoneNames[i]);
			if (pNode)
			{
				m_mapBoneTransforms.insert(make_pair(m_vecBoneNames[i], pNode->Transform()));
			}
			else
			{
				return;
			}
		}
	}
	m_bIsSet = true;
}

void CBoneHolder::SaveToLevelFile(FILE* _File)
{
}

void CBoneHolder::LoadFromLevelFile(FILE* _FILE)
{
}