#include "pch.h"
#include "CShader.h"

CShader::CShader(RES_TYPE _eType)
	: CRes(_eType, true)
{
}

CShader::~CShader()
{
}

int CShader::Load(const wstring& _strFilePath)
{
	wchar_t szFileName[512] = L"";
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, szFileName, 512, nullptr, 50);
	wstring strFileName = szFileName;
	SetName(strFileName);
	return S_OK;
}