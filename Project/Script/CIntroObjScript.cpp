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
	, m_fDuration(3.0f)
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
			pCanvas->SetUseAlpha(1);
			pCanvas->SetUITexture(m_vecTex[m_TexIdx]);
			m_TexIdx++;

			FadeIn();
		}
	}
}

void CIntroObjScript::tick()
{
	m_fTime += DT;

	if (m_fTime > 9.0f && m_TexIdx < m_vecTex.size())
	{
		m_fTime = 0.0f;
		CCanvas* pCanvas = dynamic_cast<CCanvas*>(GetOwner()->GetRenderComponent());
		if (pCanvas != nullptr)
		{
			pCanvas->SetUITexture(m_vecTex[m_TexIdx]);
			m_TexIdx++;
		}
	}

	CCanvas* pCanvas = dynamic_cast<CCanvas*>(GetOwner()->GetRenderComponent());
	if (pCanvas != nullptr)
	{
		if (m_Status == eStatus::FadeIn)
		{
			if(m_fTime > 3.0f)
				NormalState();

			if (m_fAlpha < 1.0f)
				m_fAlpha += (1.0f / (3.0f / DT));

			pCanvas->SetAlpha(m_fAlpha);
		}
		else if (m_Status == eStatus::FadeOut)
		{
			if (m_fTime > 3.0f)
				FadeIn();

			if(m_fAlpha > 0.0f)
				m_fAlpha -= (1.0f / (3.0f / DT));

			pCanvas->SetAlpha(m_fAlpha);
		}
		else
		{
			if (m_fTime > 6.0f && m_TexIdx < m_vecTex.size())
				FadeOut();

			pCanvas->SetAlpha(1.0f);
		}
	}
}

void CIntroObjScript::FadeIn()
{
	m_Status = eStatus::FadeIn;
	m_fAlpha = 0.0f;
}

void CIntroObjScript::FadeOut()
{
	m_Status = eStatus::FadeOut;
	m_fAlpha = 1.0f;
}
void CIntroObjScript::NormalState()
{
	m_Status = eStatus::None;
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
