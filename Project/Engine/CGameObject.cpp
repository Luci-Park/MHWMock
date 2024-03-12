#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CMeshRender.h"
#include "CCollider3D.h"
#include "CCapsuleCollider.h"
#include "CConvexCollider.h"
#include "CBoxCollider.h"

#include "CScript.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CRenderComponent.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_iLayerIdx(-1)
	, m_bDead(false)
	, m_LifeTime(0.f)
	, m_CurLifeTime(0.f)
	, m_bLifeSpan(false)
{
}

CGameObject::CGameObject(const CGameObject& _Other)
	: CEntity(_Other)
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_iLayerIdx(-1)
	, m_bDead(false)
	, m_LifeTime(0.f)
	, m_CurLifeTime(0.f)
	, m_bLifeSpan(false)
{
	// Component 복사
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (_Other.m_arrCom[i])
		{
			AddComponent(_Other.m_arrCom[i]->Clone());
		}
	}

	// Script 복사
	for (size_t i = 0; i < _Other.m_vecScript.size(); ++i)
	{
		AddComponent(_Other.m_vecScript[i]->Clone());
	}

	// 자식 오브젝트 복사
	for (size_t i = 0; i < _Other.m_vecChildren.size(); ++i)
	{
		AddChild(_Other.m_vecChildren[i]->Clone());
	}
	if (_Other.GetParent() != nullptr)
	{
		_Other.GetParent()->AddChild(this);
	}
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
	Safe_Del_Vec(m_vecScript);
	Safe_Del_Vec(m_vecChildren);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->begin();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->begin();
	}

	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->begin();
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->tick();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->tick();
	}

	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->tick();
	}
}

void CGameObject::finaltick()
{
	if (m_bLifeSpan)
	{
		m_CurLifeTime += DT;
		if (m_LifeTime < m_CurLifeTime)
		{
			DestroyObject(this);
		}
	}


	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::SCRIPT; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finaltick();
	}

	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->SetSiblingIdx(i);
		m_vecChildren[i]->finaltick();
	}
		
	// 소속 레이어가 없는데 finaltick 이 호출되었다.
	assert(-1 != m_iLayerIdx); 

	// 레이어 등록
	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
	pCurLayer->RegisterObject(this);
}

void CGameObject::finaltick_module()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::SCRIPT; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finaltick();
	}

	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->finaltick_module();
	}
}

void CGameObject::render()
{
	if (nullptr != m_RenderCom)
		m_RenderCom->render();
}

void CGameObject::render_shadowmap()
{
	if (nullptr != m_RenderCom)
		m_RenderCom->render_shadowmap();
}

void CGameObject::Release()
{
}

void CGameObject::AddComponent(CComponent* _Component)
{
	_Component->m_pOwner = this;

	// 컴포넌트가 스크립트인 경우
	if (COMPONENT_TYPE::SCRIPT == _Component->GetType())
	{
		m_vecScript.push_back((CScript*)_Component);
	}

	// 스크립트를 제외한 일반 컴포넌트인 경우
	else
	{		
		// 이미 보유하고 있는 컴포넌트인 경우
		assert(!m_arrCom[(UINT)_Component->GetType()]);

		m_arrCom[(UINT)_Component->GetType()] = _Component;

		// Collider3D 확인
		//CCollider3D* pCollider3D = dynamic_cast<CCollider3D*>(_Component);
		//if (pCollider3D)
		//{
		//	pCollider3D->begin();
		//}

		// RenderComponent 확인
		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Component);
		if (pRenderCom)
		{
			// 이미 1개 이상의 렌더컴포넌트를 보유하고 있다면 assert
			assert(!m_RenderCom);
			m_RenderCom = pRenderCom;
		}
	}
}

void CGameObject::AddChild(CGameObject* _Object)
{
	if (_Object->m_Parent != this)
	{
		if (_Object->m_Parent)
		{
			// 기존 부모가 있으면 연결 해제 후 연결
			_Object->DisconnectFromParent();
		}

		else
		{
			// 기존 부모가 없으면, 소속 레이어에서 최상위부모 목록에서 제거된 후 연결
			_Object->ChangeToChildType();
		}
		// 부모 자식 연결
		_Object->m_Parent = this;
	}
	_Object->SetSiblingIdx(m_vecChildren.size());
	m_vecChildren.push_back(_Object);
}

const vector<CGameObject*>& CGameObject::GetAllChildren()
{
	m_vecAllChildren.clear();
	
	for (UINT i = 0; i < m_vecChildren.size(); ++i)
	{
		PushChildObj(m_vecChildren[i]);
	}

	return m_vecAllChildren;
}

void CGameObject::PushChildObj(CGameObject* _Obj)
{
	m_vecAllChildren.push_back(_Obj);
	const vector<CGameObject*>& vecChild = _Obj->GetChildren();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		PushChildObj(vecChild[i]);
	}
}

CGameObject* CGameObject::GetRoot() const
{
	CGameObject* pParent = m_Parent;
	while (pParent->GetParent() != nullptr)	pParent = pParent->GetParent();
	return pParent;
}

CGameObject* CGameObject::FindChildByName(wstring _strName)
{
	if (GetName() == _strName)
		return this;
	for (int i = 0; i < m_vecChildren.size(); i++)
	{
		CGameObject* pObject = m_vecChildren[i]->FindChildByName(_strName);
		if (pObject != nullptr)
			return pObject;
	}
	return nullptr;
}

void CGameObject::SetParent(CGameObject* _Object)
{
	if(_Object != nullptr)
		_Object->AddChild(this);
}

void CGameObject::SetSiblingIdx(int _idx)
{
	m_iSiblingIdx = _idx;
}

bool CGameObject::IsAncestor(CGameObject* _Target)
{
	CGameObject* pParent = m_Parent;
	while (pParent)
	{
		if (pParent == _Target)
		{
			return true;
		}
		pParent = pParent->m_Parent;
	}

	return false;
}

void CGameObject::DisconnectFromParent()
{
	if (!m_Parent)
		return;

	vector<CGameObject*>::iterator iter = m_Parent->m_vecChildren.begin();
	for (; iter != m_Parent->m_vecChildren.end(); ++iter)
	{
		if (this == *iter)
		{
			m_Parent->m_vecChildren.erase(iter);
			m_Parent = nullptr;
			return;
		}
	}

	assert(nullptr);
}

void CGameObject::ChangeToChildType()
{
	assert(-1 <= m_iLayerIdx && m_iLayerIdx < MAX_LAYER);

	if (-1 != m_iLayerIdx)
	{
		CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
		pLayer->RemoveFromParentList(this);
	}
}

void CGameObject::AddParentList()
{
	CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_iLayerIdx);
	pLayer->AddParentList(this);
}

void CGameObject::AddCollider3D(SHAPE_TYPE _type, ACTOR_TYPE _actorType)
{
	CGameObject* owner = this;
	switch (_type)
	{
	case SHAPE_TYPE::CUBE:
		owner->AddComponent(new CBoxCollider);
		break;
	case SHAPE_TYPE::CAPSULE:
		owner->AddComponent(new CCapsuleCollider);
		break;
	case SHAPE_TYPE::CONVEX:
		owner->AddComponent(new CConvexCollider);
		break;
	}
	CCollider3D* coll = dynamic_cast<CCollider3D*>(m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER3D]);
	//setting Actor type
	coll->SetActorType(_actorType);
	coll->begin();
}

//Remove Component Func
int CGameObject::DeleteComponent(COMPONENT_TYPE _type)
{
	//Detect can not be Remove Component
	if (_type == COMPONENT_TYPE::TRANSFORM)
		return FALSE;

	//if it possible remove component
	CComponent* comp = m_arrCom[(UINT)_type];
	m_arrCom[(UINT)_type] = nullptr;

	//if it is Render Component also remove and than release memory
	CRenderComponent* RC;
	if (RC = dynamic_cast<CRenderComponent*>(comp))
		m_RenderCom = nullptr;
	delete comp;

	return TRUE;
}

CComponent* CGameObject::GetComponentInParent(COMPONENT_TYPE _CType)
{
	if (m_arrCom[(UINT)_CType]) return m_arrCom[(UINT)_CType];
	if (m_Parent != nullptr && m_Parent != this)
	{
		return m_Parent->GetComponentInParent(_CType);
	}
	return nullptr;
}
