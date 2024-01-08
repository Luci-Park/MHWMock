#include "pch.h"
#include "LayerInfoUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CLayer.h>

LayerInfoUI::LayerInfoUI()
	: ObjectInfoUI("##Layer", OBJINFO_TYPE::LAYER)
{
	SetName("Layer");
}


LayerInfoUI::~LayerInfoUI()
{
}
int LayerInfoUI::render_update()
{
	if (FALSE == ObjectInfoUI::render_update())
		return FALSE;

	// Layer¶ç¿ì±â
	int iLayerIdx = GetTarget()->GetLayerIndex();
	string strLayerName = ToString((LAYER_TYPE)iLayerIdx);

	char szBuff[50] = {};
	strcpy(szBuff, strLayerName.c_str());

	ImGui::Text("Layer    ");
	ImGui::SameLine();
	ImGui::Text(szBuff);

	//ImGui::InputText("##LayerName", szBuff, 50, ImGuiInputTextFlags_ReadOnly);


	return TRUE;
}


