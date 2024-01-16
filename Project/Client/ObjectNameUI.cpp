#include "pch.h"
#include "ObjectNameUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CLayer.h>

ObjectNameUI::ObjectNameUI()
	: ObjectInfoUI("##Obj_Name", OBJINFO_TYPE::Obj_Name)
{
	SetName("Obj_Name");
}

ObjectNameUI::~ObjectNameUI()
{
}

int ObjectNameUI::render_update()
{
	if (FALSE == ObjectInfoUI::render_update())
		return FALSE;

	// GameObj 이름 변경
	wstring TargetName = GetTarget()->GetName();
	string sTargetName = string(TargetName.begin(), TargetName.end());
	
	//sTargetName.assign(TargetName.begin(), TargetName.end());
	char szTargetName_buff[50] = {};
	strcpy_s(szTargetName_buff, sTargetName.c_str());

	ImGui::Text("ObjectName ");
	ImGui::SameLine();
	ImGui::InputText(" ", szTargetName_buff, 50, ImGuiInputTextFlags_AlwaysOverwrite);

	sTargetName = szTargetName_buff;
	GetTarget()->SetName(TargetName.assign(sTargetName.begin(), sTargetName.end()));

	return TRUE;
}


