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
    vector<tAnimationKeyFrame> m_vecRsltChannel;
public:
    vector<tAnimationKeyFrame>& GetTransformsAtFrame(double _dTick);
private:
    Vec3 FindVector3AtFrame(double _dTick, vector<tAnimationKey>& _vecKeys, AnimBehaviour _PreState, AnimBehaviour _PostState);
    virtual int Load(const wstring& _strFilePath);

public:
    virtual int Save(const wstring& _strFilePath);

    static CAnimationClip* LoadFromAssimp(aiAnimation* _aiAnimation);

    CAnimationClip();
    ~CAnimationClip();
};

