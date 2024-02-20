#include "pch.h"
#include "CFont.h"

#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24 ) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)

CFont::CFont()
	: CComponent(COMPONENT_TYPE::FONT)
{
	m_Text.Content = L"TEST";
	m_Text.FontColor = FONT_RGBA(0.f, 0.f, 0.f, 255.f);
	m_Text.FontPos = Vec2(10.f, 30.0f);
	m_Text.FontSize = 10.0f;
}

CFont::~CFont()
{
}

void CFont::finaltick()
{
	CTextMgr::GetInst()->AddText(m_Text);
}

void CFont::SetFont(Vec4 _Color, Vec2 _Pos, float _Size)
{
	UINT Fcolor = FONT_RGBA(_Color.x, _Color.y, _Color.z, _Color.w);
	m_Text.FontColor = Fcolor;
	m_Text.FontPos = _Pos;
	m_Text.FontSize = _Size;
}

void CFont::SaveToLevelFile(FILE* _File)
{
}

void CFont::LoadFromLevelFile(FILE* _File)
{
}
