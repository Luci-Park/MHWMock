#pragma once
#include "CRes.h"
class CModel :
	public CRes
{
private:

public:
    virtual int Save(const wstring& _strRelativePath) { return S_OK; }
private:
    virtual int Load(const wstring& _strFilePath);
public:
    CModel();
    ~CModel();
};

