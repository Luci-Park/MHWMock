#pragma once
#include "CSingleton.h"

class CTextMgr
	: public CSingleton<CTextMgr>
{
public:
	CTextMgr();
	~CTextMgr();

	void init();
	void render();

	void AddText(TextInfo text) { m_Texts.push_back(text); }

private:
	vector<TextInfo> m_Texts;

};

