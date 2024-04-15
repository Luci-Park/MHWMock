#include "pch.h"
#include "CScript.h"


CScript::CScript(UINT _ScriptType)
	: CComponent(COMPONENT_TYPE::SCRIPT)	
	, m_iScriptType(_ScriptType)
	, m_bGameObjectParamSet(false)
{
}

CScript::~CScript()
{
}

void CScript::AddScriptParam(SCRIPT_PARAM eParam, void* _pData, const string& _Desc)
{
	m_vecParam.push_back(tScriptParam{ eParam , _pData , _Desc });

	if (eParam == SCRIPT_PARAM::GAMEOBJECT)
	{
		m_vecParamObjs.push_back((CGameObject**)_pData);
		m_vecGameObjParams.resize(m_vecParamObjs.size());
	}
}
void CScript::tick()
{
	FindGameObject();
	update();
}
void CScript::finaltick()
{
	FindGameObject();
}


void CScript::SaveGameObjectParam(CGameObject* _Obj, FILE* _File)
{
	int i = _Obj != nullptr;
	fwrite(&i, sizeof(int), 1, _File);
	if (!i) return;

	list<int> idxs;
	CGameObject* trav = _Obj;
	CGameObject* finalParent = _Obj;
	while (trav != nullptr)
	{
		idxs.push_front(trav->GetSiblingIdx());
		finalParent = trav;
		trav = trav->GetParent();
	}
	idxs.push_front(finalParent->GetLayerIndex());
	int temp = idxs.size();
	fwrite(&temp, sizeof(int), 1, _File);
	for (int idx : idxs)
		fwrite(&idx, sizeof(int), 1, _File);
}

void CScript::LoadGameObjectParam(int _vecIdx, FILE* _File)
{
	m_vecGameObjParams[_vecIdx].clear();

	int temp;
	fread(&temp, sizeof(int), 1, _File);
	if (!temp) return;

	fread(&temp, sizeof(int), 1, _File);
	while (temp--)
	{
		int t;
		fread(&t, sizeof(int), 1, _File);
		m_vecGameObjParams[_vecIdx].push_back(t);
	}
	m_vecGameObjParams[_vecIdx].push_front(0);
	m_bGameObjectParamSet = false;
}

void CScript::FindGameObject()
{
	if (m_bGameObjectParamSet) return;
	CLevel* curLv = CLevelMgr::GetInst()->GetCurLevel();
	int count = 0;
	for (size_t i = 0; i < m_vecGameObjParams.size(); i++)
	{
		list<int>& idxs = m_vecGameObjParams[i];
		if (!idxs.empty())
		{
			if (idxs.front())
			{
				++count;
				continue;
			}
			auto iter = idxs.begin(); iter++;
			CLayer* layer = curLv->GetLayer(*iter); iter++;

			CGameObject* obj = layer->GetParentObject()[*iter]; iter++;

			for (; iter != m_vecGameObjParams[i].end() && obj != nullptr; iter++)
				obj = obj->GetChild(*iter);

			if (obj == nullptr) continue;
			idxs.front() = 1;
			*m_vecParamObjs[i] = obj;
		}
		++count;
	}
	if (count == m_vecGameObjParams.size()) m_bGameObjectParamSet = true;
}
