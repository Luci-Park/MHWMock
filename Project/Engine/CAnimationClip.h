#pragma once
#include "CRes.h"

class CAnimationClip :
	public CRes
{
private:
    // 파일로부터 로딩
    virtual int Load(const wstring& _strFilePath);

public:
    // 파일로 저장
    virtual int Save(const wstring& _strFilePath);

    CAnimationClip();
    ~CAnimationClip();
};

