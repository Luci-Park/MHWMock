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
    // ���Ϸκ��� �ε�
    virtual int Load(const wstring& _strFilePath);

public:
    // ���Ϸ� ����
    virtual int Save(const wstring& _strFilePath);

    static CAnimationClip* LoadFromAssimp(aiAnimation* _aiAnimation);

    CAnimationClip();
    ~CAnimationClip();
};

