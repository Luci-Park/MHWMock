#include "pch.h"
#include "CArenaScript.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CRenderComponent.h>
#include <Engine/CCanvas.h>

#include <Engine/CKeyMgr.h>
#include <Engine/CEventMgr.h>
#include "../Client/CLevelSaveLoad.h"
#include "CCompleteScript.h"

CArenaScript::CArenaScript()
	: CScript((UINT)SCRIPT_TYPE::ARENASCRIPT)
	, m_fTime(0.0f)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pCompleteObj, "Target Obj");

}


CArenaScript::~CArenaScript()
{
}



void CArenaScript::begin()
{
	CResMgr::GetInst()->FindRes<CSound>(L"sound\\2-13 Arena Large Monsters Abound.mp3")->Play(100, 1.0, true);

}

void CArenaScript::tick()
{
	if (m_fTime <= 10.0f && m_fTime > 0.0f)
	{
		m_fTime += DT;
	}
	else
	{
		m_fTime = -100.0f;
		CompleteQuest();
	}
}


void CArenaScript::CompleteQuest()
{
	m_bComplete = true;
	CResMgr::GetInst()->FindRes<CSound>(L"sound\\2-13 Arena Large Monsters Abound.mp3")->Stop();

	CCompleteScript* pCompleteScript = dynamic_cast<CCompleteScript*>(m_pCompleteObj->GetRenderComponent());
	if (pCompleteScript != nullptr)
	{
		pCompleteScript->FadeIn();
	}
}

void CArenaScript::SaveToLevelFile(FILE* _File)
{
	SaveGameObjectParam(m_pCompleteObj, _File);
}

void CArenaScript::LoadFromLevelFile(FILE* _FILE)
{
	LoadGameObjectParam(0, _FILE);
}

