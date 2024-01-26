#include "pch.h"
#include "CAnimationClip.h"
#include "ptr.h"
#include <assimp/scene.h>

CAnimationClip::CAnimationClip()
	: CRes(RES_TYPE::ANIMATION, true)
{
}

CAnimationClip::~CAnimationClip()
{
}

CAnimationClip* CAnimationClip::LoadFromAssimp(aiAnimation* _aiAnimation)
{
	CAnimationClip* pAnim = new CAnimationClip();
	
	string strName = _aiAnimation->mName.C_Str();	
	pAnim->SetName(wstring(strName.begin(), strName.end()));

	pAnim->m_dDuration = _aiAnimation->mDuration;
	pAnim->m_dTicksPerSecond = _aiAnimation->mTicksPerSecond;
	pAnim->m_BoneNames.resize(_aiAnimation->mNumChannels);
	pAnim->m_vecChannels.resize(_aiAnimation->mNumChannels);

	for (size_t i = 0; i < _aiAnimation->mNumChannels; i++)
	{
		aiNodeAnim* pChannel = _aiAnimation->mChannels[i];
		string strBName = pChannel->mNodeName.C_Str();
		pAnim->m_BoneNames[i] = wstring(strBName.begin(), strBName.end());
		pAnim->m_vecChannels[i].vecPositionKeys.resize(pChannel->mNumPositionKeys);
		pAnim->m_vecChannels[i].vecRotationKeys.resize(pChannel->mNumRotationKeys);
		pAnim->m_vecChannels[i].vecScaleKeys.resize(pChannel->mNumScalingKeys);
		for (size_t j = 0; j < pChannel->mNumPositionKeys; j++)
		{
			auto v3 = pChannel->mPositionKeys[j].mValue;
			pAnim->m_vecChannels[i].vecPositionKeys[j].vValue =
				Vec3(v3.x, v3.y, v3.z);
			
			pAnim->m_vecChannels[i].vecPositionKeys[j].dTime = 
				pChannel->mPositionKeys[j].mTime;
		}
		
		for (size_t j = 0; j < pChannel->mNumRotationKeys; j++)
		{
			auto qQuat = pChannel->mRotationKeys[j].mValue;
			auto qQ = Quaternion(qQuat.x, qQuat.y, qQuat.z, qQuat.w);

			pAnim->m_vecChannels[i].vecRotationKeys[j].vValue =
				qQ.ToEuler();

			pAnim->m_vecChannels[i].vecRotationKeys[j].dTime =
				pChannel->mRotationKeys[j].mTime;
		}

		for (size_t j = 0; j < pChannel->mNumScalingKeys; j++)
		{
			auto v3 = pChannel->mScalingKeys[j].mValue;
			pAnim->m_vecChannels[i].vecScaleKeys[j].vValue =
				Vec3(v3.x, v3.y, v3.z);

			pAnim->m_vecChannels[i].vecScaleKeys[j].dTime =
				pChannel->mScalingKeys[j].mTime;
		}
	}
	

	return pAnim;
}

int CAnimationClip::Load(const wstring& _strFilePath)
{
	return 0;
}

int CAnimationClip::Save(const wstring& _strFilePath)
{
	return 0;
}

