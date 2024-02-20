#pragma once
#include "CComponent.h"
#include "CFontMgr.h"
#include "CTextMgr.h"

class CFont :
	public CComponent
{
public:
	CFont();
	~CFont();

	CLONE(CFont);

	virtual void finaltick() override;

	void SetFont(Vec4 _Color, Vec2 _Pos, float _Size);
	void SetContent(wstring _Content) { m_Text.Content = _Content; }

	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _File) override;

private:

	TextInfo m_Text;
};

