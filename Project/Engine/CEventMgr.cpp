#include "pch.h"
#include "CEventMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"
#include "CResMgr.h"
#include "CRenderMgr.h"
#include "CLayer.h"
#include "components.h"

CEventMgr::CEventMgr()
	: m_LevelChanged(false)
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::tick()
{
	m_LevelChanged = false;

	GC_Clear();

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].Type)
		{
		// wParam : GameObject, lParam : Layer Index
		case EVENT_TYPE::CREATE_OBJECT:
		{
			CGameObject* NewObject = (CGameObject*)m_vecEvent[i].wParam;
			int iLayerIdx = (int)m_vecEvent[i].lParam;

			CLevelMgr::GetInst()->GetCurLevel()->AddGameObject(NewObject, iLayerIdx, false);
			if (CLevelMgr::GetInst()->GetCurLevel()->GetState() == LEVEL_STATE::PLAY)
			{
				NewObject->begin();
			}

			m_LevelChanged = true;
		}
			break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			CGameObject* DeleteObject = (CGameObject*)m_vecEvent[i].wParam;

			if (false == DeleteObject->m_bDead)
			{
				DeleteObject->m_bDead = true;
				m_vecGC.push_back(DeleteObject);
			}			
		}
		break;

		case EVENT_TYPE::LOAD_OBJECT:
		{
			CGameObject* pObj = (CGameObject*)m_vecEvent[i].wParam;
			SpawnGameObject(pObj, pObj->Transform()->GetRelativePos(), pObj->GetLayerIndex());
			m_LevelChanged = true;
		}
		break;

		case EVENT_TYPE::ADD_CHILD:
			// wParam : ParentObject, lParam : ChildObject
		{
			CGameObject* pDestObj = (CGameObject*)m_vecEvent[i].wParam;
			CGameObject* pSrcObj = (CGameObject*)m_vecEvent[i].lParam;

			// �θ�� ������ ������Ʈ�� ������, Child ������Ʈ�� �ֻ��� �θ� ������Ʈ�� �ȴ�.
			if (nullptr == pDestObj)
			{
				if (pSrcObj->GetParent())
				{
					// ���� �θ���� ���� ����
					pSrcObj->DisconnectFromParent();
					// �ֻ��� �θ� ������Ʈ��, �Ҽ� ���̾ ���
					pSrcObj->AddParentList();
				}
			}
			else
			{
				pDestObj->AddChild(pSrcObj);
			}

			m_LevelChanged = true;
		}
			

		
			break;
		case EVENT_TYPE::DELETE_RESOURCE:
			// wParam : RES_TYPE, lParam : Resource Adress
		{
			RES_TYPE type = (RES_TYPE)m_vecEvent[i].wParam;
			CRes* pRes = (CRes*)m_vecEvent[i].lParam;
			CResMgr::GetInst()->DeleteRes(type, pRes->GetKey());
		}

			break;
		case EVENT_TYPE::LAYER_CHANGE:
			// wParam : Obj, lParam : DestLayerName
		{
			CGameObject* pObj = (CGameObject*)m_vecEvent[i].wParam;
			LAYER_TYPE DestType = (LAYER_TYPE)m_vecEvent[i].lParam;
			int iPrevLayerIdx = pObj->GetLayerIndex();

			// �θ����� �ڽ����� üũ
			if (pObj->m_Parent)
			{
				// �ڽ��ΰ�� LayerIndex �ٲ��ָ��.
				pObj->SetLayerIndex((int)DestType);
			}
			else
			{
				// �θ��ΰ�� vecParentList���� �� DestLayer�� ��� + LayerIdx����
				//RemoveFromParentList
				//AddParentList
				CLayer* pPrevLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(iPrevLayerIdx);
				CLayer* pDestLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer((int)DestType);

				pPrevLayer->RemoveFromParentList(pObj);
				pDestLayer->AddParentList(pObj);
				pObj->SetLayerIndex((int)DestType);
			}

			m_LevelChanged = true;
		}
			break;
		
		case EVENT_TYPE::LEVEL_CHANGE:
		{
			// wParam : Level Adress
			CLevel* Level = (CLevel*)m_vecEvent[i].wParam;
			CLevelMgr::GetInst()->ChangeLevel(Level);
			CRenderMgr::GetInst()->ClearCamera();
			m_LevelChanged = true;
		}
			break;

		case EVENT_TYPE::CHANGE_OBJECT:
		{
			m_LevelChanged = true;
		}
		break;
		}
	}

	m_vecEvent.clear();
}


void CEventMgr::GC_Clear()
{
	for (size_t i = 0; i < m_vecGC.size(); ++i)
	{
		if (nullptr != m_vecGC[i])
		{
			// �ڽ� Ÿ�� ������Ʈ�� ���
			if (m_vecGC[i]->GetParent())			
				m_vecGC[i]->DisconnectFromParent();
			
			delete m_vecGC[i];

			m_LevelChanged = true;
		}		
	}
	m_vecGC.clear();
}