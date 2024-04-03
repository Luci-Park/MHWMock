#include "pch.h"
#include "CIntroObjScript.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CRenderComponent.h>
#include <Engine/CCanvas.h>


CIntroObjScript::CIntroObjScript()
	: CScript((UINT)SCRIPT_TYPE::INTROOBJSCRIPT)
	, m_Status(eStatus::None)
	, m_fTime(0.0f)
	, m_fAlpha(0.0f)
	, m_TexIdx(0)
{
	m_vecTex.push_back(0);
	m_vecTex.push_back(0);
	m_vecTex.push_back(0);
	m_vecTex.push_back(0);

	AddScriptParam(SCRIPT_PARAM::TEXTURE, &m_vecTex[0], "Tex 01");
	AddScriptParam(SCRIPT_PARAM::TEXTURE, &m_vecTex[1], "Tex 02");
	AddScriptParam(SCRIPT_PARAM::TEXTURE, &m_vecTex[2], "Tex 03");
	AddScriptParam(SCRIPT_PARAM::TEXTURE, &m_vecTex[3], "Tex 04");
}

CIntroObjScript::~CIntroObjScript()
{
}

void CIntroObjScript::begin()
{
	if (m_vecTex[0] != nullptr)
	{
		CCanvas* pCanvas = dynamic_cast<CCanvas*>(GetOwner()->GetRenderComponent());
		if (pCanvas != nullptr)
		{
			pCanvas->SetUITexture(m_vecTex[m_TexIdx]);
			m_TexIdx++;
		}
	}
}

void CIntroObjScript::tick()
{
	m_fTime += DT;

	if (m_fTime > 15.0f && m_TexIdx < m_vecTex.size())
	{
		m_fTime = 0.0f;
		CCanvas* pCanvas = dynamic_cast<CCanvas*>(GetOwner()->GetRenderComponent());
		if (pCanvas != nullptr)
		{
			pCanvas->SetUITexture(m_vecTex[m_TexIdx]);
			m_TexIdx++;
		}
	}
}

void CIntroObjScript::FadeIn()
{
}

void CIntroObjScript::FadeOut()
{
}
void CIntroObjScript::SaveToLevelFile(FILE* _File)
{
	SaveResRef(m_vecTex[0].Get(), _File);
	SaveResRef(m_vecTex[1].Get(), _File);
	SaveResRef(m_vecTex[2].Get(), _File);
	SaveResRef(m_vecTex[3].Get(), _File);

}

void CIntroObjScript::LoadFromLevelFile(FILE* _FILE)
{
	LoadResRef(m_vecTex[0], _FILE);
	LoadResRef(m_vecTex[1], _FILE);
	LoadResRef(m_vecTex[2], _FILE);
	LoadResRef(m_vecTex[3], _FILE);
}
