#include "pch.h"
#include "CTextMgr.h"
#include "CFontMgr.h"


CTextMgr::CTextMgr()
{
}

CTextMgr::~CTextMgr()
{
}

void CTextMgr::init()
{
	m_Texts.clear();
}

void CTextMgr::render()
{
	wchar_t szBuff[256] = {0,};

	for (TextInfo text : m_Texts)
	{
		swprintf_s(szBuff, text.Content.data());
		CFontMgr::GetInst()->DrawFont(szBuff, text.FontPos.x, text.FontPos.y, text.FontSize, text.FontColor);
	}
	m_Texts.clear();
}
