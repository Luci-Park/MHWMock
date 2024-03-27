#include "pch.h"
#include "CAnimationClip.h"
#include <assimp/scene.h>
#include "CPathMgr.h"
//#include "Assimp.hpp"

CAnimationClip::CAnimationClip()
	: CRes(RES_TYPE::ANIMATION)
	, m_dDuration(0)
	, m_dTicksPerSecond(30)
{
}

CAnimationClip::~CAnimationClip()
{
}

CAnimationClip* CAnimationClip::CreateFromAssimp(aiAnimation* _aiAnimation)
{
	CAnimationClip* pAnim = new CAnimationClip();
	
	string strName = _aiAnimation->mName.C_Str();
	auto pos = strName.find_last_of('|');
	if (pos != string::npos)
		strName = strName.substr(pos + 1);

	pAnim->SetName(wstring(strName.begin(), strName.end()));

	pAnim->m_dDuration = _aiAnimation->mDuration;
	pAnim->m_dTicksPerSecond = _aiAnimation->mTicksPerSecond;

	for (size_t i = 0; i < _aiAnimation->mNumChannels; i++)
	{
		aiNodeAnim* pChannel = _aiAnimation->mChannels[i];
		wstring strBName = STR2WSTR(pChannel->mNodeName.C_Str());
		pAnim->m_RsltKeyFrame.emplace(strBName, tAnimationKeyFrame(strBName));

		auto channel = pAnim->m_Channels.emplace(strBName, tAnimationChannel()).first;
		channel->second.strBoneName = strBName;
		
		channel->second.vecPositionKeys.resize(pChannel->mNumPositionKeys);
		channel->second.vecRotationKeys.resize(pChannel->mNumRotationKeys);
		channel->second.vecScaleKeys.resize(pChannel->mNumScalingKeys);
		channel->second.ePreState = (AnimBehaviour)pChannel->mPreState;
		channel->second.ePostState = (AnimBehaviour)pChannel->mPostState;

		for (size_t j = 0; j < pChannel->mNumPositionKeys; j++)
		{
			auto v3 = pChannel->mPositionKeys[j].mValue;
			channel->second.vecPositionKeys[j].value = Vec3(v3.x, v3.y, v3.z);			
			channel->second.vecPositionKeys[j].time = pChannel->mPositionKeys[j].mTime;
		}
		
		for (size_t j = 0; j < pChannel->mNumRotationKeys; j++)
		{

			auto qQuat = pChannel->mRotationKeys[j].mValue;
			channel->second.vecRotationKeys[j].value = Quaternion(qQuat.x, qQuat.y, qQuat.z, qQuat.w);
			channel->second.vecRotationKeys[j].time = pChannel->mRotationKeys[j].mTime;
		}

		for (size_t j = 0; j < pChannel->mNumScalingKeys; j++)
		{
			auto v3 = pChannel->mScalingKeys[j].mValue;
			channel->second.vecScaleKeys[j].value =	Vec3(v3.x, v3.y, v3.z);
			channel->second.vecScaleKeys[j].time = pChannel->mScalingKeys[j].mTime;
		}
	}

	return pAnim;
}

KeyFrames& CAnimationClip::GetTransformsAtFrame(double _dTick)
{
	for (auto& iter : m_RsltKeyFrame)
	{
		iter.second.strBoneName = iter.first;
		auto channel = m_Channels.find(iter.first);
		assert(channel != m_Channels.end());
		iter.second.vPos = FindValueAtFrame(_dTick, channel->second.vecPositionKeys, channel->second.ePreState, channel->second.ePostState);
		iter.second.qRot = FindValueAtFrame(_dTick, channel->second.vecRotationKeys, channel->second.ePreState, channel->second.ePostState);
		iter.second.vScale = FindValueAtFrame(_dTick, channel->second.vecScaleKeys, channel->second.ePreState, channel->second.ePostState);
	}
	return m_RsltKeyFrame;
}

Vec3 CAnimationClip::FindValueAtFrame(double _dTick, vector<tVecAnimationKey>& _vecKeys, AnimBehaviour _PreState, AnimBehaviour _PostState)
{
	int idx = 0;
	for (; idx < _vecKeys.size(); idx++)
	{
		if (_dTick <= _vecKeys[idx].time)
			break;
	}
	if (idx == 0)
	{
		double t = _dTick / _vecKeys[idx].time;
		return _vecKeys[idx].value;
	}
	else if (idx < _vecKeys.size())
	{
		double a = _vecKeys[idx - 1].time;
		double b = _vecKeys[idx].time;
		double t = (_dTick - a) / (b - a);
		return Vector3::Lerp(_vecKeys[idx - 1].value, _vecKeys[idx].value, t);
		
	}
	else
	{
		double t = _dTick / _vecKeys[idx - 1].time;
		return _vecKeys[idx - 1].value;
	}
}

Quaternion CAnimationClip::FindValueAtFrame(double _dTick, vector<tQuatAnimationKey>& _vecKeys, AnimBehaviour _PreState, AnimBehaviour _PostState)
{
	int idx = 0;
	for (; idx < _vecKeys.size(); idx++)
	{
		if (_dTick <= _vecKeys[idx].time)
			break;
	}
	if (idx == 0)
	{
		double t = _dTick / _vecKeys[idx].time;
		return _vecKeys[idx].value;
	}
	else if (idx < _vecKeys.size())
	{
		double a = _vecKeys[idx - 1].time;
		double b = _vecKeys[idx].time;
		double t = (_dTick - a) / (b - a);
		return Quaternion::Lerp(_vecKeys[idx - 1].value, _vecKeys[idx].value, t);

	}
	else
	{
		double t = _dTick / _vecKeys[idx - 1].time;
		return _vecKeys[idx - 1].value;
	}
}

int CAnimationClip::Save(const wstring& _strRelativePath)
{
	if (IsEngineRes())
		return E_FAIL;

	try
	{
		SetRelativePath(_strRelativePath);
		wstring strFilePath = CPathMgr::GetInst()->GetContentPath() + _strRelativePath;

		path parentFolder(strFilePath);
		filesystem::create_directories(parentFolder.parent_path());

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

		if (pFile == nullptr)
			return E_FAIL;

		SaveWString(GetName(), pFile);
		SaveWString(GetKey(), pFile);

		fwrite(&m_dDuration, sizeof(double), 1, pFile);
		fwrite(&m_dTicksPerSecond, sizeof(double), 1, pFile);

		UINT iSize = m_Channels.size();
		fwrite(&iSize, sizeof(UINT), 1, pFile);
		for (auto channel : m_Channels)
		{
			SaveWString(channel.second.strBoneName, pFile);
			if (channel.second.Save(pFile) == E_FAIL)
				return E_FAIL;
		}

		fclose(pFile);
		return S_OK;
	}
	catch (const std::exception&)
	{
		return E_FAIL;
	}
}

int CAnimationClip::Load(const wstring& _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");
	if (pFile == nullptr)
		return E_FAIL;

	wstring name, key;
	LoadWString(name, pFile);
	LoadWString(key, pFile);

	SetName(name);
	SetKey(key);

	fread(&m_dDuration, sizeof(double), 1, pFile);
	fread(&m_dTicksPerSecond, sizeof(double), 1, pFile);

	UINT iSize;
	fread(&iSize, sizeof(UINT), 1, pFile);
	for (size_t i = 0; i < iSize; i++)
	{
		wstring boneName;
		LoadWString(boneName, pFile);
		m_RsltKeyFrame.emplace(boneName, tAnimationKeyFrame(boneName));
		auto reslt = m_Channels.emplace(boneName, tAnimationChannel());
		reslt.first->second.strBoneName = boneName;
		reslt.first->second.Load(pFile);
	}

	fclose(pFile);

	//Save(key);

	return S_OK;
}

