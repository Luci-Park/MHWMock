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

	// Layer띄우기
	int iLayerIdx = GetTarget()->GetLayerIndex();
	string strLayerName = ToString((LAYER_TYPE)iLayerIdx);

	char szBuff[50] = {};
	strcpy(szBuff, strLayerName.c_str());

	ImGui::Text("Layer		");
	ImGui::SameLine();
	ImGui::Text(szBuff);

	//ImGui::InputText("##LayerName", szBuff, 50, ImGuiInputTextFla5gs_ReadOnly);


	// GameObj 이름 변경
	wstring TargetName = GetTarget()->GetName();
	string sTargetName;
	sTargetName.assign(TargetName.begin(), TargetName.end());
	char szTargetName_buff[50] = {};
	strcpy(szTargetName_buff, sTargetName.c_str());


	ImGui::Text("ObjectName ");
	ImGui::SameLine();
	ImGui::InputText(" ", szTargetName_buff, 50, ImGuiInputTextFlags_AlwaysOverwrite);

	sTargetName = szTargetName_buff;
	GetTarget()->SetName(TargetName.assign(sTargetName.begin(), sTargetName.end()));
	

	return TRUE;
}


