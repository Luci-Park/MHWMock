#include "pch.h"
#include "ModelUI.h"

#include <Engine/CModel.h>

ModelUI::ModelUI() :
	ResUI(RES_TYPE::MODEL)
{
	SetName("Model");
}

ModelUI::~ModelUI()
{
}

int ModelUI::render_update()
{
	ResUI::render_update();

    ImGui::Text("Model   ");
    ImGui::SameLine();

    Ptr<CModel> pModel = (CModel*)GetTargetRes().Get();
    string strKey = string(pModel->GetKey().begin(), pModel->GetKey().end());
    ImGui::InputText("##ModelUIName", (char*)strKey.c_str(), strKey.length(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

    return 0;
}