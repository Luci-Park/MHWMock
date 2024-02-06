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

			// 부모로 지정된 오브젝트가 없으면, Child 오브젝트가 최상위 부모 오브젝트가 된다.
			if (nullptr == pDestObj)
			{
				if (pSrcObj->GetParent())
				{
					// 기존 부모와의 연결 해제
					pSrcObj->DisconnectFromParent();
					// 최상위 부모 오브젝트로, 소속 레이어에 등록
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

			// 부모인지 자식인지 체크
			if (pObj->m_Parent)
			{
				// 자식인경우 LayerIndex 바꿔주면됨.
				pObj->SetLayerIndex((int)DestType);
			}
			else
			{
				// 부모인경우 vecParentList삭제 후 DestLayer에 등록 + LayerIdx수정
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
			// 자식 타입 오브젝트인 경우
			if (m_vecGC[i]->GetParent())			
				m_vecGC[i]->DisconnectFromParent();
			
			delete m_vecGC[i];

			m_LevelChanged = true;
		}		
	}
	m_vecGC.clear();
}