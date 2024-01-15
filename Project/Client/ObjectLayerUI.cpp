#include "pch.h"
#include "ObjectLayerUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CLayer.h>

ObjectLayerUI::ObjectLayerUI()
	: ObjectInfoUI("##Obj_Layer", OBJINFO_TYPE::Obj_Layer)
{
	SetName("Obj_Layer");
}


ObjectLayerUI::~ObjectLayerUI()
{
}
int ObjectLayerUI::render_update()
{
	if (FALSE == ObjectInfoUI::render_update())
		return FALSE;

	// Layer����
	int iLayerIdx = GetTarget()->GetLayerIndex();
	string strLayerName = ToString((LAYER_TYPE)iLayerIdx);

	char szBuff[50] = {};
	strcpy(szBuff, strLayerName.c_str());

	ImGui::Text("Layer		");
	ImGui::SameLine();
	ImGui::Text(szBuff);
	//ImGui::InputText("##LayerName", szBuff, 50, ImGuiInputTextFla5gs_ReadOnly);
	
	return TRUE;
}

