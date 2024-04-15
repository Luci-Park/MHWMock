#include "pch.h"
#include "CCompleteScript.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CRenderComponent.h>
#include <Engine/CCanvas.h>

#include <Engine/CKeyMgr.h>
#include <Engine/CEventMgr.h>
#include "../Client/CLevelSaveLoad.h"

CCompleteScript::CCompleteScript()
	: CScript((UINT)SCRIPT_TYPE::COMPLETESCRIPT)
	, m_fAlpha(0.0f)
	, m_bUseObj(false)
	, m_bFadeIn(false)
	, m_bIsPlayed(false)
{
	AddScriptParam(SCRIPT_PARAM::TEXTURE, &m_Tex, "Tex");
}

CCompleteScript::~CCompleteScript()
{
}
void CCompleteScript::begin()
{
	// Test용
	// ArenaScript에 몬스터가 죽었을경우 발생하도록 구현
	CCanvas* pCanvas = dynamic_cast<CCanvas*>(GetOwner()->GetRenderComponent());
	if(pCanvas)
	{
		pCanvas->SetUITexture(m_Tex);
		pCanvas->SetUseAlpha(2);
	}
	//FadeIn();
}

void CCompleteScript::update()
{
	if (m_bUseObj)
	{
		if (!m_bIsPlayed)
		{
			m_bIsPlayed = true;
			CResMgr::GetInst()->FindRes<CSound>(L"sound\\1-17 Quest Complete! (Proof of a Hero version).mp3")->Play(1, 1.0, true);

		}
		if (m_bFadeIn)
		{
			CCanvas* pCanvas = dynamic_cast<CCanvas*>(GetOwner()->GetRenderComponent());

			if(m_fAlpha <= 1.0f)
				m_fAlpha += (1.0f / 3.0f) * DT;
			else
			{
				pCanvas->SetAlpha(1.0f);
				m_bFadeIn = false;
			}
				
			if (pCanvas)
			{
				pCanvas->SetAlpha(m_fAlpha);
			}
		}
		else
		{
			// Credit or Title로 이동?
			if (KEY_TAP(KEY::SPACE))
			{
				CResMgr::GetInst()->FindRes<CSound>(L"sound\\1 - 17 Quest Complete!(Proof of a Hero version).mp3")->Stop();
			}
		}
	}
}

void CCompleteScript::FadeIn()
{
	m_bFadeIn = true;
	m_bUseObj = true;
	m_fAlpha = 0.0f;
}

void CCompleteScript::SaveToLevelFile(FILE* _File)
{
	SaveResRef(m_Tex.Get(), _File);
}

void CCompleteScript::LoadFromLevelFile(FILE* _FILE)
{
	LoadResRef(m_Tex, _FILE);
}


