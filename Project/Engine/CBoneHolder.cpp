#include "pch.h"
#include "CBoneHolder.h"
#include "CTransform.h"


CBoneHolder::CBoneHolder(set<wstring> _boneNames)
	: CComponent(COMPONENT_TYPE::BONEHOLDER)
	, m_bIsSet(false)
	, m_setBoneNames(_boneNames)
{
}

CBoneHolder::CBoneHolder(const CBoneHolder& _other)
	: CComponent(_other)
	, m_setBoneNames(_other.m_setBoneNames)
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
	for (auto name : m_setBoneNames)
	{
		auto node = m_mapBoneTransforms.find(name);
		if (node == m_mapBoneTransforms.end())
		{
			CGameObject* pNode = GetOwner()->FindChildByName(name);
			if (pNode)
			{
				m_mapBoneTransforms.insert(make_pair(name, pNode->Transform()));
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