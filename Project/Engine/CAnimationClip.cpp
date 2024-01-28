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
	pAnim->m_vecRsltChannel.resize(_aiAnimation->mNumChannels);

	for (size_t i = 0; i < _aiAnimation->mNumChannels; i++)
	{
		aiNodeAnim* pChannel = _aiAnimation->mChannels[i];
		string strBName = pChannel->mNodeName.C_Str();
		pAnim->m_BoneNames[i] = wstring(strBName.begin(), strBName.end());
		pAnim->m_vecRsltChannel[i].strBoneName = pAnim->m_BoneNames[i];
		pAnim->m_vecChannels[i].vecPositionKeys.resize(pChannel->mNumPositionKeys);
		pAnim->m_vecChannels[i].vecRotationKeys.resize(pChannel->mNumRotationKeys);
		pAnim->m_vecChannels[i].vecScaleKeys.resize(pChannel->mNumScalingKeys);

		pAnim->m_vecChannels[i].ePreState = (AnimBehaviour)pChannel->mPreState;
		pAnim->m_vecChannels[i].ePostState = (AnimBehaviour)pChannel->mPostState;

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

vector<tAnimationKeyFrame>& CAnimationClip::GetTransformsAtFrame(double _dTick)
{
	for (int i = 0; i < m_vecChannels.size(); i++)
	{
		m_vecRsltChannel[i].vPos = FindVector3AtFrame(_dTick, m_vecChannels[i].vecPositionKeys, m_vecChannels[i].ePreState, m_vecChannels[i].ePostState);
		m_vecRsltChannel[i].vRot = FindVector3AtFrame(_dTick, m_vecChannels[i].vecRotationKeys, m_vecChannels[i].ePreState, m_vecChannels[i].ePostState);
		m_vecRsltChannel[i].vScale = FindVector3AtFrame(_dTick, m_vecChannels[i].vecScaleKeys, m_vecChannels[i].ePreState, m_vecChannels[i].ePostState);
	}
	return m_vecRsltChannel;
}

Vec3 CAnimationClip::FindVector3AtFrame(double _dTick, vector<tAnimationKey>& _vecKeys, AnimBehaviour _PreState, AnimBehaviour _PostState)
{
	int idx = 0;
	for (; idx < _vecKeys.size(); idx++)
	{
		if (_dTick <= _vecKeys[idx].dTime)
			break;
	}
	if (idx == 0)
	{
		double t = _dTick / _vecKeys[idx].dTime;
		return _vecKeys[idx].vValue;
	}
	else if (idx == _vecKeys.size())
	{
		double a = _vecKeys[idx - 1].dTime;
		double b = _vecKeys[idx].dTime;
		double t = (_dTick - a) / (b - a);
		return Vector3::Lerp(_vecKeys[idx].vValue, _vecKeys[idx - 1].vValue, t);
		
	}
	else
	{
		double t = _dTick / _vecKeys[idx].dTime;
		return _vecKeys[idx].vValue;
	}
}

int CAnimationClip::Load(const wstring& _strFilePath)
{
	return 0;
}

int CAnimationClip::Save(const wstring& _strFilePath)
{
	return 0;
}

