#include "pch.h"
#include "ObjectInfoUI.h"

#include <Engine\CGameObject.h>

ObjectInfoUI::ObjectInfoUI(const string& _Name, OBJINFO_TYPE _Type)
	: UI(_Name)
	, m_Type(_Type)
{
}

ObjectInfoUI::~ObjectInfoUI()
{

}

void ObjectInfoUI::SetTarget(CGameObject* _Target)
{
	m_Target = _Target;

	if (nullptr == m_Target)
	{
		SetActive(false);
		return;
	}

	m_Target = _Target;

	if (nullptr == m_Target)
	{
		SetActive(false);
		return;
	}
	else
	{
		SetActive(true);
		return;
	}
}

int ObjectInfoUI::render_update()
{
	if (nullptr == m_Target)
		return FALSE;

	//ImGui::PushID(0);
	//ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	//ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	//ImGui::Button(GetName().c_str());
	//ImGui::PopStyleColor(3);
	//ImGui::PopID();

	return TRUE;
}


