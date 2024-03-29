#include "pch.h"
#include "CScriptMgr.h"

#include "CAnjanath.h"
#include "CAnjanathPart.h"
#include "CCameraMoveScript.h"
#include "CGravityScript.h"
#include "CMainPlayerScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlayerCameraScript.h"
#include "CPlayerScript.h"
#include "CPlayerShieldScript.h"
#include "CSwordScript.h"
#include "CTestScript.h"
#include "CWeaponScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CAnjanath");
	_vec.push_back(L"CAnjanathPart");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CGravityScript");
	_vec.push_back(L"CMainPlayerScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlayerCameraScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CSwordScript");
	_vec.push_back(L"CPlayerShieldScript");
	_vec.push_back(L"CTestScript");
	_vec.push_back(L"CWeaponScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CAnjanath" == _strScriptName)
		return new CAnjanath;
	if (L"CAnjanathPart" == _strScriptName)
		return new CAnjanathPart;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CGravityScript" == _strScriptName)
		return new CGravityScript;
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
	if (L"CSwordScript" == _strScriptName)
		return new CSwordScript;
	if (L"CPlayerShieldScript" == _strScriptName)
		return new CPlayerShieldScript;
	if (L"CTestScript" == _strScriptName)
		return new CTestScript;
	if (L"CWeaponScript" == _strScriptName)
		return new CWeaponScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::ANJANATH:
		return new CAnjanath;
		break;
	case (UINT)SCRIPT_TYPE::ANJANATHPART:
		return new CAnjanathPart;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::GRAVITYSCRIPT:
		return new CGravityScript;
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
	case (UINT)SCRIPT_TYPE::SWORDSCRIPT:
		return new CSwordScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSHIELDSCRIPT:
		return new CPlayerShieldScript;
		break;
	case (UINT)SCRIPT_TYPE::TESTSCRIPT:
		return new CTestScript;
		break;
	case (UINT)SCRIPT_TYPE::WEAPONSCRIPT:
		return new CWeaponScript;
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

	case SCRIPT_TYPE::ANJANATHPART:
		return L"CAnjanathPart";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::GRAVITYSCRIPT:
		return L"CGravityScript";
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

	case SCRIPT_TYPE::SWORDSCRIPT:
		return L"CSwordScript";
		break;

	case SCRIPT_TYPE::PLAYERSHIELDSCRIPT:
		return L"CPlayerShieldScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"CTestScript";
		break;

	case SCRIPT_TYPE::WEAPONSCRIPT:
		return L"CWeaponScript";
		break;

	}
	return nullptr;
}