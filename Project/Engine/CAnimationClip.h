#pragma once
#include "CRes.h"

class CAnimationClip :
	public CRes
{
private:
    // ���Ϸκ��� �ε�
    virtual int Load(const wstring& _strFilePath);

public:
    // ���Ϸ� ����
    virtual int Save(const wstring& _strFilePath);

    CAnimationClip();
    ~CAnimationClip();
};

