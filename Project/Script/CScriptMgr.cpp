#include "pch.h"
#include "CScriptMgr.h"

#include "CAnjanath.h"
#include "CAnjanathBody.h"
#include "CAnjanathHead.h"
#include "CAnjanathLeftLeg.h"
#include "CAnjanathRightLeg.h"
#include "CAnjanathTail.h"
#include "CArenaScript.h"
#include "CCameraMoveScript.h"
#include "CCompleteScript.h"
#include "CGravityScript.h"
#include "CIntroObjScript.h"
#include "CMainPlayerScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlayerCameraScript.h"
#include "CPlayerScript.h"
#include "CPlayerShieldScript.h"
#include "CSwordScript.h"
#include "CTestScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CAnjanath");
	_vec.push_back(L"CAnjanathBody");
	_vec.push_back(L"CAnjanathHead");
	_vec.push_back(L"CAnjanathLeftLeg");
	_vec.push_back(L"CAnjanathRightLeg");
	_vec.push_back(L"CAnjanathTail");
	_vec.push_back(L"CArenaScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CCompleteScript");
	_vec.push_back(L"CGravityScript");
	_vec.push_back(L"CIntroObjScript");
	_vec.push_back(L"CMainPlayerScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlayerCameraScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPlayerShieldScript");
	_vec.push_back(L"CSwordScript");
	_vec.push_back(L"CTestScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CAnjanath" == _strScriptName)
		return new CAnjanath;
	if (L"CAnjanathBody" == _strScriptName)
		return new CAnjanathBody;
	if (L"CAnjanathHead" == _strScriptName)
		return new CAnjanathHead;
	if (L"CAnjanathLeftLeg" == _strScriptName)
		return new CAnjanathLeftLeg;
	if (L"CAnjanathRightLeg" == _strScriptName)
		return new CAnjanathRightLeg;
	if (L"CAnjanathTail" == _strScriptName)
		return new CAnjanathTail;
	if (L"CArenaScript" == _strScriptName)
		return new CArenaScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CCompleteScript" == _strScriptName)
		return new CCompleteScript;
	if (L"CGravityScript" == _strScriptName)
		return new CGravityScript;
	if (L"CIntroObjScript" == _strScriptName)
		return new CIntroObjScript;
	if (L"CMainPlayerScript" == _strScriptName)
		return new CMainPlayerScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlayerCameraScript" == _strScriptName)
		return new CPlayerCameraScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPlayerShieldScript" == _strScriptName)
		return new CPlayerShieldScript;
	if (L"CSwordScript" == _strScriptName)
		return new CSwordScript;
	if (L"CTestScript" == _strScriptName)
		return new CTestScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::ANJANATH:
		return new CAnjanath;
		break;
	case (UINT)SCRIPT_TYPE::ANJANATHBODY:
		return new CAnjanathBody;
		break;
	case (UINT)SCRIPT_TYPE::ANJANATHHEAD:
		return new CAnjanathHead;
		break;
	case (UINT)SCRIPT_TYPE::ANJANATHLEFTLEG:
		return new CAnjanathLeftLeg;
		break;
	case (UINT)SCRIPT_TYPE::ANJANATHRIGHTLEG:
		return new CAnjanathRightLeg;
		break;
	case (UINT)SCRIPT_TYPE::ANJANATHTAIL:
		return new CAnjanathTail;
		break;
	case (UINT)SCRIPT_TYPE::ARENASCRIPT:
		return new CArenaScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::COMPLETESCRIPT:
		return new CCompleteScript;
		break;
	case (UINT)SCRIPT_TYPE::GRAVITYSCRIPT:
		return new CGravityScript;
		break;
	case (UINT)SCRIPT_TYPE::INTROOBJSCRIPT:
		return new CIntroObjScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINPLAYERSCRIPT:
		return new CMainPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERCAMERASCRIPT:
		return new CPlayerCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSHIELDSCRIPT:
		return new CPlayerShieldScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDSCRIPT:
		return new CSwordScript;
		break;
	case (UINT)SCRIPT_TYPE::TESTSCRIPT:
		return new CTestScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::ANJANATH:
		return L"CAnjanath";
		break;

	case SCRIPT_TYPE::ANJANATHBODY:
		return L"CAnjanathBody";
		break;

	case SCRIPT_TYPE::ANJANATHHEAD:
		return L"CAnjanathHead";
		break;

	case SCRIPT_TYPE::ANJANATHLEFTLEG:
		return L"CAnjanathLeftLeg";
		break;

	case SCRIPT_TYPE::ANJANATHRIGHTLEG:
		return L"CAnjanathRightLeg";
		break;

	case SCRIPT_TYPE::ANJANATHTAIL:
		return L"CAnjanathTail";
		break;

	case SCRIPT_TYPE::ARENASCRIPT:
		return L"CArenaScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::COMPLETESCRIPT:
		return L"CCompleteScript";
		break;

	case SCRIPT_TYPE::GRAVITYSCRIPT:
		return L"CGravityScript";
		break;

	case SCRIPT_TYPE::INTROOBJSCRIPT:
		return L"CIntroObjScript";
		break;

	case SCRIPT_TYPE::MAINPLAYERSCRIPT:
		return L"CMainPlayerScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLAYERCAMERASCRIPT:
		return L"CPlayerCameraScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::PLAYERSHIELDSCRIPT:
		return L"CPlayerShieldScript";
		break;

	case SCRIPT_TYPE::SWORDSCRIPT:
		return L"CSwordScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"CTestScript";
		break;

	}
	return nullptr;
}