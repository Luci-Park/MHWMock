#pragma once
#include "UI.h"

class TreeUI;
class TreeNode;

class OutlinerUI :
    public UI
{
private:
    TreeUI*     m_Tree;
    DWORD_PTR   m_dwSelectedData;


public:
    virtual void tick() override;
    virtual int render_update() override;

public:
    void ResetOutliner();
    void SetTargetToInspector(DWORD_PTR _SelectedNode);
    CGameObject* GetSelectedObject();

    // Ʈ���� ���µ� ���, �Է����� ���� �����Ϳ� ������ ��带  ���û��·� �д�.
    void SetSelectedNodeData(DWORD_PTR _data)
    {
        m_dwSelectedData = _data;
    }

private:
    void ChangeParent(DWORD_PTR _DragNode, DWORD_PTR _DropNode);
    void ChangeLayer(DWORD_PTR _DragNode, DWORD_PTR _DropNode);

private:
    void AddGameObject(CGameObject* _Obj, TreeNode* _ParentNode);
    void DragDrop(DWORD_PTR _DragNode, DWORD_PTR _DropNode);



public:
    OutlinerUI();
    ~OutlinerUI();
};

