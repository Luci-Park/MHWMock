#include "pch.h"
#include "ModelUI.h"
#include "MaterialUI.h"
#include "MeshUI.h"

#include <Engine/CModel.h>
ModelUI::ModelUI() :
	ResUI(RES_TYPE::MODEL)
    , m_pMaterialUI()
    , m_pMeshUI()
{
	SetName("Model");
}

ModelUI::~ModelUI()
{
    delete m_pMaterialUI;
    m_pMaterialUI = nullptr;
    delete m_pMeshUI;
    m_pMeshUI = nullptr;
}

int ModelUI::render_update()
{
	ResUI::render_update();

    ImGui::Text("Model   ");
    ImGui::SameLine();

    Ptr<CModel> pModel = (CModel*)GetTargetRes().Get();
    string strKey = string(pModel->GetKey().begin(), pModel->GetKey().end());
    ImGui::InputText("##ModelUIName", (char*)strKey.c_str(), strKey.length(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

    render_update_node(pModel->GetRootNode());
    return 0;
}

void ModelUI::render_update_node(tModelNode* _pNode)
{
    string strName = string(_pNode->strName.begin(), _pNode->strName.end());
    ImGui::InputText("##ModelNodeName", (char*)strName.c_str(), strName.length(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
    if (_pNode->pMesh != nullptr)
    {
        m_pMeshUI->SetTargetRes((CRes*)_pNode->pMesh.Get());
        m_pMeshUI->SetActive(true);
    }
    else
    {
        m_pMeshUI->SetActive(false);
    }
    if (_pNode->pMaterial != nullptr)
    {
        m_pMaterialUI->SetTargetRes((CRes*)_pNode->pMaterial.Get());
        m_pMaterialUI->SetActive(true);
    }
    else
    {
        m_pMaterialUI->SetActive(false);
    }
    for (int i = 0; i < _pNode->vecChildren.size(); i++)
    {
        render_update_node(_pNode->vecChildren[i]);
    }
}
