#pragma once
#include "CRes.h"

class aiAnimation;
class CAnimationClip :
	public CRes
{
private:
    double                    m_dDuration; //by ticks
    double                    m_dTicksPerSecond;
    vector<tAnimationChannel> m_vecChannels;
    vector<wstring>           m_BoneNames;
private:
    // 파일로부터 로딩
    virtual int Load(const wstring& _strFilePath);

public:
    // 파일로 저장
    virtual int Save(const wstring& _strFilePath);

    static CAnimationClip* LoadFromAssimp(aiAnimation* _aiAnimation);

    CAnimationClip();
    ~CAnimationClip();
};

