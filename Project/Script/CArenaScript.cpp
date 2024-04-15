#include "pch.h"
#include "CArenaScript.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CRenderComponent.h>
#include <Engine/CCanvas.h>

#include <Engine/CKeyMgr.h>
#include <Engine/CEventMgr.h>
#include "../Client/CLevelSaveLoad.h"
#include "CCompleteScript.h"
#include "CAnjanath.h"

CArenaScript::CArenaScript()
	: CScript((UINT)SCRIPT_TYPE::ARENASCRIPT)
	, m_fTime(0.0f)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pCompleteObj, "Complete Obj");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_Monster, "Monster Obj");

}


CArenaScript::~CArenaScript()
{
}



void CArenaScript::begin()
{
	CResMgr::GetInst()->FindRes<CSound>(L"sound\\2-13 Arena Large Monsters Abound.mp3")->Play(100, 0.1f, true);
}

void CArenaScript::tick()
{
	CAnjanath* pMonsterScript = m_Monster->GetScript<CAnjanath>();
	int iMonsterHp = pMonsterScript->HP();
	
	if (iMonsterHp < 0)
	{
		CompleteQuest();
	}
}


void CArenaScript::CompleteQuest()
{
	m_bComplete = true;
	CResMgr::GetInst()->FindRes<CSound>(L"sound\\2-13 Arena Large Monsters Abound.mp3")->Stop();

	CCompleteScript* pCompleteScript = m_pCompleteObj->GetScript<CCompleteScript>();
	if (pCompleteScript != nullptr)
	{
		pCompleteScript->FadeIn();
	}
}

void CArenaScript::SaveToLevelFile(FILE* _File)
{
	SaveGameObjectParam(m_pCompleteObj, _File);
	SaveGameObjectParam(m_Monster, _File);
}

void CArenaScript::LoadFromLevelFile(FILE* _FILE)
{
	LoadGameObjectParam(0, _FILE);
	//LoadGameObjectParam(1, _FILE);
}

