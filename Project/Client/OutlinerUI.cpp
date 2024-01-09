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

	// OutlinerUI �ȿ� �ڽ����� Tree �� �߰��Ѵ�.
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

		// Ʈ�� ���� ��, ���� ���ó��� ������ DATA �� ������, ã�Ƽ� ���ó��� ����
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

	// ���� �Ŵ������� ���� ���� �޾ƿ�.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT i = 0; i < (UINT)MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		
		// Layer OutlineUI�� ����
		if (ToString(pLayer->GetLayerType()) != "")
		{
			// Layer->GetName() = wstring�̱� ������ string�̿��Ͽ� ��ȯ.
			TreeNode* pCategory = m_Tree->AddItem(ToString(pLayer->GetLayerType()), 0);
			pCategory->SetCategoryNode(true);

			const vector<CGameObject*>& vecParentObj = pLayer->GetParentObject();

			// Layer�� ������ü�� GameObj ����
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

	// Inspector �� ���õ� GameObject �� �˷��ش�.	
	InspectorUI* pInspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetObject(pSelectObject);
}




void OutlinerUI::AddGameObject(CGameObject* _Obj, TreeNode* _ParentNode)
{
	// ������Ʈ�� Ʈ���� �ְ�, ������ ��� �ּҸ� �޾Ƶд�.
	TreeNode* pNode = m_Tree->AddItem(string(_Obj->GetName().begin(), _Obj->GetName().end())
									, (DWORD_PTR)_Obj
									, _ParentNode);

	// ������Ʈ�� �ڽĿ�����Ʈ ���� ������Ʈ ��带 �θ�� �ؼ� �� ������ �ٽ� �־��ش�.
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

	// pDragNode�� m_Data�� 0 �̶�� Obj�� �ƴϴ�.
	// pDragNode�� ������ Obj������.
	if (nullptr == (CGameObject*)pDragNode->GetData())
		return;

	// 1. pDropNode�� Layer���� �Ǻ�
	// DropNode�� �����ϸ鼭 pDropNode�� m_Data�� 0 �̶�� = LayerCategory
	if (nullptr != pDropNode && nullptr == (CGameObject*)pDropNode->GetData())
	{
		// 2. pDropNode�� �̸� �����͸� �̿��Ͽ� EventMgr���� LayerChange �����ֱ�.
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

	// �ڽ����� �� ������Ʈ�� ������ ������Ʈ�� ����(�θ����) �� �ϳ����, 
	// AddChild ó������ �ʴ´�.
	if (nullptr != pDropNode)
	{
		pDropObj = (CGameObject*)pDropNode->GetData();
	}

	if (nullptr != pDropObj)
	{
		if (pDropObj->IsAncestor(pDragObj))
			return;
	}

	// �̺�Ʈ �Ŵ����� ���ؼ� ó���Ѵ�.
	tEvent evn = {};
	evn.Type = EVENT_TYPE::ADD_CHILD;
	evn.wParam = (DWORD_PTR)pDropObj;
	evn.lParam = (DWORD_PTR)pDragObj;
	CEventMgr::GetInst()->AddEvent(evn);
}

