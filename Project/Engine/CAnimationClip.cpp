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
			pAnim->m_vecChannels[i].vecPositionKeys[j].value =
				Vec3(v3.x, v3.y, v3.z);
			
			pAnim->m_vecChannels[i].vecPositionKeys[j].time = 
				pChannel->mPositionKeys[j].mTime;
		}
		
		for (size_t j = 0; j < pChannel->mNumRotationKeys; j++)
		{

			auto qQuat = pChannel->mRotationKeys[j].mValue;

			pAnim->m_vecChannels[i].vecRotationKeys[j].value =
				Quaternion(qQuat.x, qQuat.y, qQuat.z, qQuat.w);

			pAnim->m_vecChannels[i].vecRotationKeys[j].time =
				pChannel->mRotationKeys[j].mTime;
		}

		for (size_t j = 0; j < pChannel->mNumScalingKeys; j++)
		{
			auto v3 = pChannel->mScalingKeys[j].mValue;
			pAnim->m_vecChannels[i].vecScaleKeys[j].value =
				Vec3(v3.x, v3.y, v3.z);

			pAnim->m_vecChannels[i].vecScaleKeys[j].time =
				pChannel->mScalingKeys[j].mTime;
		}
	}

	return pAnim;
}

vector<tAnimationKeyFrame>& CAnimationClip::GetTransformsAtFrame(double _dTick)
{
	for (int i = 0; i < m_vecChannels.size(); i++)
	{
		m_vecRsltChannel[i].strBoneName = m_BoneNames[i];
		m_vecRsltChannel[i].vPos = FindValueAtFrame(_dTick, m_vecChannels[i].vecPositionKeys, m_vecChannels[i].ePreState, m_vecChannels[i].ePostState);
		m_vecRsltChannel[i].qRot = FindValueAtFrame(_dTick, m_vecChannels[i].vecRotationKeys, m_vecChannels[i].ePreState, m_vecChannels[i].ePostState);
		m_vecRsltChannel[i].vScale = FindValueAtFrame(_dTick, m_vecChannels[i].vecScaleKeys, m_vecChannels[i].ePreState, m_vecChannels[i].ePostState);
	}
	return m_vecRsltChannel;
}

int CAnimationClip::GetRootIdx(wstring _rootName)
{
	for (int i = 0; i < m_BoneNames.size(); i++)
		if (m_BoneNames[i] == _rootName)
			return i;
	return -1;
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

		UINT iSize = m_vecChannels.size();
		fwrite(&iSize, sizeof(UINT), 1, pFile);
		for (size_t i = 0; i < iSize; i++)
		{
			m_vecChannels[i].strBoneName = m_BoneNames[i];
			if (m_vecChannels[i].Save(pFile) == E_FAIL)
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
	m_vecChannels.resize(iSize);
	for (size_t i = 0; i < iSize; i++)
		m_vecChannels[i].Load(pFile);

	fread(&iSize, sizeof(UINT), 1, pFile);
	m_BoneNames.resize(iSize);
	for (size_t i = 0; i < iSize; i++)
		LoadWString(m_BoneNames[i], pFile);

	fread(&iSize, sizeof(UINT), 1, pFile);
	m_vecRsltChannel.resize(iSize);
	for (size_t i = 0; i < iSize; i++)
	{
		LoadWString(m_vecRsltChannel[i].strBoneName, pFile);
		fread(&m_vecRsltChannel[i].vPos, sizeof(Vec3), 1, pFile);
		fread(&m_vecRsltChannel[i].qRot, sizeof(Quaternion), 1, pFile);
		fread(&m_vecRsltChannel[i].vScale, sizeof(Vec3), 1, pFile);
	}

	fclose(pFile);

	//Save(_strFilePath);

	return S_OK;
}

