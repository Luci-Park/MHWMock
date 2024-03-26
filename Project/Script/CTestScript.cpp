#include "pch.h"
#include "CTestScript.h"


CTestScript::CTestScript()
	: CScript((UINT)SCRIPT_TYPE::TESTSCRIPT)
{
}

CTestScript::~CTestScript()
{
}


void CTestScript::begin()
{
}

void CTestScript::tick()
{
}

void CTestScript::OnAnimationBegin(IAnimationState* _pState)
{
	int i = 0;
}

void CTestScript::OnAnimationEndStart(IAnimationState* _pState)
{
	int j = 0;
}

void CTestScript::OnAnimationEndFinished(IAnimationState* _pState)
{
	int p = 0;
}

void CTestScript::SaveToLevelFile(FILE* _File)
{
}

void CTestScript::LoadFromLevelFile(FILE* _FILE)
{
}


