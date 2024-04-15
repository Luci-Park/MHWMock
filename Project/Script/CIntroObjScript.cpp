#include "pch.h"
#include "CIntroObjScript.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CRenderComponent.h>
#include <Engine/CCanvas.h>

#include <Engine/CKeyMgr.h>
#include <Engine/CEventMgr.h>
#include "../Client/CLevelSaveLoad.h"

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
	m_wNextLevelName = L"level\\Arena.lv";

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

void CIntroObjScript::update()
{
	m_fTime += DT;

	CCanvas* pCanvas = dynamic_cast<CCanvas*>(GetOwner()->GetRenderComponent());
	if (m_fTime > 6.0f && m_TexIdx < m_vecTex.size())
	{
		m_fTime = 0.0f;
		if (pCanvas != nullptr)
		{
			pCanvas->SetUITexture(m_vecTex[m_TexIdx]);
			FadeIn();
			m_TexIdx++;
		}
	}

	if (pCanvas != nullptr)
	{
		if (m_Status == eStatus::FadeIn)
		{
			if (m_fAlpha > 1.0f)
			{
				pCanvas->SetAlpha(1.0f);
				NormalState();
			}
			else
			{
				m_fAlpha += (1.0f / 2.0f) * DT;
			}

			pCanvas->SetAlpha(m_fAlpha);
		}
		else if (m_Status == eStatus::FadeOut)
		{
			if (m_fAlpha <= 0.0f)
			{
				m_fAlpha = 0.0f;
			}
			else
			{
				m_fAlpha -= (1.0f / 2.0f) * DT;
			}

			pCanvas->SetAlpha(m_fAlpha);
		}
		else
		{
			if (m_fTime > 4.0f && m_TexIdx < m_vecTex.size())
				FadeOut();
		}
	}

	if (m_TexIdx >= m_vecTex.size())
	{
		if (!m_bIsChanged)
		{
			CResMgr::GetInst()->FindRes<CSound>(L"sound\\1-01 Main Theme - Stars at Our Backs.mp3")->Play(1, 0.2f, true);

			if (KEY_TAP(KEY::SPACE))
			{
				int a = 0;
				// 다음레벨로 넘어가도록 처리
				CResMgr::GetInst()->FindRes<CSound>(L"sound\\1-01 Main Theme - Stars at Our Backs.mp3")->Stop();
				CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(m_wNextLevelName);

				tEvent evn = {};
				evn.Type = EVENT_TYPE::LEVEL_CHANGE;
				evn.wParam = (DWORD_PTR)pLoadedLevel;

				CEventMgr::GetInst()->AddEvent(evn);
				//pLoadedLevel->ChangeState(LEVEL_STATE::PLAY);
				m_bIsChanged = true;
			}
		}
		else
		{
			/*CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
			CurLevel->ChangeState(LEVEL_STATE::PLAY);*/
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
