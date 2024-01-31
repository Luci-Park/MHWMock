#include "pch.h"
#include "ObjNameInfoUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CLayer.h>
#include <Engine\CEventMgr.h>

ObjNameInfoUI::ObjNameInfoUI()
	: ObjectInfoUI("##Obj_Name", OBJINFO_TYPE::Obj_Name)
{
	SetName("Obj_Name");
}

ObjNameInfoUI::~ObjNameInfoUI()
{
}
int ObjNameInfoUI::render_update()
{
	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::Button("ObjectInfo");
	ImGui::PopStyleColor(3);
	ImGui::PopID();

	if (FALSE == ObjectInfoUI::render_update())
		return FALSE;

	if (GetTarget()->IsDead())
		return FALSE;

	// GameObj 이름 변경
	wstring TargetName = GetTarget()->GetName();
	string sTargetName;
	sTargetName.assign(TargetName.begin(), TargetName.end());
	char szTargetName_buff[50] = {};
	strcpy_s(szTargetName_buff, sTargetName.c_str());


	ImGui::Text("ObjectName ");
	ImGui::SameLine();
	ImGui::InputText(" ", szTargetName_buff, 50, ImGuiInputTextFlags_AlwaysOverwrite);

	if (sTargetName != szTargetName_buff)
	{
		sTargetName = szTargetName_buff;
		GetTarget()->SetName(TargetName.assign(sTargetName.begin(), sTargetName.end()));
		tEvent evn = {};
		evn.wParam = (DWORD_PTR)GetTarget();
		evn.lParam = (DWORD_PTR)1;
		evn.Type = EVENT_TYPE::CHANGE_OBJECT;
		CEventMgr::GetInst()->AddEvent(evn);

		return TRUE;
	}
}


