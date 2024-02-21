#include "pch.h"
#include "CollisionUI.h"

#include "TreeUI.h"
#include "ImGuiMgr.h"
#include "InspectorUI.h"

CollisionUI::CollisionUI()
	: UI("##Collision")
{
	SetName("Collision");

    // ContentUI �ȿ� �ڽ����� Tree �� �߰��Ѵ�.
    m_Tree = new TreeUI;
    m_Tree->SetName("CollisionTree");
    m_Tree->SetActive(true);
    m_Tree->ShowRoot(false);

    AddChildUI(m_Tree);

}

CollisionUI::~CollisionUI()
{
}


void CollisionUI::init()
{
}

void CollisionUI::tick()
{
    UI::tick();
}

int CollisionUI::render_update()
{
    return 0;
}

