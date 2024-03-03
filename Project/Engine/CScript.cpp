#include "pch.h"
#include "CScript.h"


CScript::CScript(UINT _ScriptType)
	: CComponent(COMPONENT_TYPE::SCRIPT)	
	, m_iScriptType(_ScriptType)
{
}

CScript::~CScript()
{
}

void CScript::AddScriptParam(SCRIPT_PARAM eParam, void* _pData, const string& _Desc)
{
	m_vecParam.push_back(tScriptParam{ eParam , _pData , _Desc });
}

void CScript::SetScriptObjParam(UINT _Idx, CGameObject* _Obj)
{
	if (_Obj != nullptr)
		m_vecParam[_Idx].pData = _Obj;
}
