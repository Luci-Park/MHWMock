#include "pch.h"
#include "OutlinerUI.h"

#include "ImGuiMgr.h"
#include "InspectorUI.h"

#include <Engine\CEventMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "TreeUI.h"

OutlinerUI::OutlinerUI()
    : UI("##Outliner")
	, m_Tree(nullptr)
{
    SetName("Outliner");

	// OutlinerUI 안에 자식으로 Tree 를 추가한다.
	m_Tree = new TreeUI;
	m_Tree->SetName("OutlinerTree");
	m_Tree->SetActive(true);
	m_Tree->ShowRoot(false);

	m_Tree->AddDynamic_Select(this, (UI_DELEGATE_1)&OutlinerUI::SetTargetToInspector);
	m_Tree->AddDynamic_DragDrop(this, (UI_DELEGATE_2)&OutlinerUI::DragDrop);
	m_Tree->SetDragDropID("GameObject");


	AddChildUI(m_Tree);
}

OutlinerUI::~OutlinerUI()
{
}

void OutlinerUI::tick()
{
	if (CEventMgr::GetInst()->IsLevelChanged())
	{
		ResetOutliner();

		// 트리 리셋 후, 다음 선택노드로 지정된 DATA 가 있으면, 찾아서 선택노드로 변경
		if (0 != m_dwSelectedData)
		{
			m_Tree->GetSelectedNode(m_dwSelectedData);
		}		
	}
}

int OutlinerUI::render_update()
{
    return 0;
}


void OutlinerUI::ResetOutliner()
{
	// Tree Clear
	m_Tree->Clear();
	m_Tree->AddItem("Root", 0);

	// 레벨 매니저에서 현재 레밸 받아옴.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT i = 0; i < (UINT)MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		
		// Layer OutlineUI에 띄우기
		if (ToString(pLayer->GetLayerType()) != "")
		{
			// Layer->GetName() = wstring이기 때문에 string이용하여 변환.
			TreeNode* pCategory = m_Tree->AddItem(ToString(pLayer->GetLayerType()), 0);
			pCategory->SetCategoryNode(true);

			const vector<CGameObject*>& vecParentObj = pLayer->GetParentObject();

			// Layer의 하위객체로 GameObj 띄우기
			for (size_t i = 0; i < vecParentObj.size(); ++i)
			{
				AddGameObject(vecParentObj[i], pCategory);
			}
		}
	}
}

void OutlinerUI::SetTargetToInspector(DWORD_PTR _SelectedNode)
{
	TreeNode* pSelectedNode = (TreeNode*)_SelectedNode;
	CGameObject* pSelectObject = (CGameObject*)pSelectedNode->GetData();

	// Inspector 에 선택된 GameObject 를 알려준다.	
	InspectorUI* pInspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetObject(pSelectObject);
}




void OutlinerUI::AddGameObject(CGameObject* _Obj, TreeNode* _ParentNode)
{
	// 오브젝트를 트리에 넣고, 생성된 노드 주소를 받아둔다.
	TreeNode* pNode = m_Tree->AddItem(string(_Obj->GetName().begin(), _Obj->GetName().end())
									, (DWORD_PTR)_Obj
									, _ParentNode);

	// 오브젝트의 자식오브젝트 들을 오브젝트 노드를 부모로 해서 그 밑으로 다시 넣어준다.
	const vector<CGameObject*>& vecChild = _Obj->GetChild();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddGameObject(vecChild[i], pNode);
	}
}


CGameObject* OutlinerUI::GetSelectedObject()
{
	TreeNode* pSelectedNode = m_Tree->GetSelectedNode();

	if (nullptr == pSelectedNode)
		return nullptr;

	return (CGameObject*)pSelectedNode->GetData();
}






void OutlinerUI::DragDrop(DWORD_PTR _DragNode, DWORD_PTR _DropNode)
{
	TreeNode* pDragNode = (TreeNode*)_DragNode;
	TreeNode* pDropNode = (TreeNode*)_DropNode;

	// pDragNode의 m_Data가 0 이라면 Obj가 아니다.
	// pDragNode는 무조건 Obj여야함.
	if (nullptr == (CGameObject*)pDragNode->GetData())
		return;

	// 1. pDropNode가 Layer인지 판별
	// DropNode가 존재하면서 pDropNode의 m_Data가 0 이라면 = LayerCategory
	if (nullptr != pDropNode && nullptr == (CGameObject*)pDropNode->GetData())
	{
		// 2. pDropNode의 이름 데이터를 이용하여 EventMgr에서 LayerChange 시켜주기.
		ChangeLayer(_DragNode, _DropNode);
		return;
	}

	ChangeParent(_DragNode, _DropNode);
}

void OutlinerUI::ChangeLayer(DWORD_PTR _DragNode, DWORD_PTR _DropNode)
{
	TreeNode* pDragNode = (TreeNode*)_DragNode;
	TreeNode* pDropNode = (TreeNode*)_DropNode;

	CGameObject* pDragObj = (CGameObject*)pDragNode->GetData();
	const string& pDropLayerName = pDropNode->GetName();

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	LAYER_TYPE pDropLayerType = (LAYER_TYPE)pCurLevel->FindLayerIdxByName(pDropLayerName);

	tEvent evn = {};
	evn.Type = EVENT_TYPE::LAYER_CHANGE;
	evn.wParam = (DWORD_PTR)pDragObj;
	evn.lParam = (DWORD_PTR)pDropLayerType;
	CEventMgr::GetInst()->AddEvent(evn);
}

void OutlinerUI::ChangeParent(DWORD_PTR _DragNode, DWORD_PTR _DropNode)
{
	TreeNode* pDragNode = (TreeNode*)_DragNode;
	TreeNode* pDropNode = (TreeNode*)_DropNode;

	CGameObject* pDragObj = (CGameObject*)pDragNode->GetData();
	CGameObject* pDropObj = nullptr;

	// 자식으로 들어갈 오브젝트가 목적지 오브젝트의 조상(부모계층) 중 하나라면, 
	// AddChild 처리하지 않는다.
	if (nullptr != pDropNode)
	{
		pDropObj = (CGameObject*)pDropNode->GetData();
	}

	if (nullptr != pDropObj)
	{
		if (pDropObj->IsAncestor(pDragObj))
			return;
	}

	// 이벤트 매니저를 통해서 처리한다.
	tEvent evn = {};
	evn.Type = EVENT_TYPE::ADD_CHILD;
	evn.wParam = (DWORD_PTR)pDropObj;
	evn.lParam = (DWORD_PTR)pDragObj;
	CEventMgr::GetInst()->AddEvent(evn);
}

