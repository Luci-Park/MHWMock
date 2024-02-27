#include "pch.h"
#include "ComponentUI.h"

#include <Engine\CGameObject.h>

ComponentUI::ComponentUI(const string& _Name, COMPONENT_TYPE _Type)
	: UI(_Name)
	, m_Type(_Type)
{
}

ComponentUI::~ComponentUI()
{
	
}

int ComponentUI::render_update()
{
	if (nullptr == m_Target || nullptr == m_Target->GetComponent(m_Type) || m_Target->IsDead())
		return FALSE;

	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::Button(GetName().c_str());
	ImGui::PopStyleColor(3);
	ImGui::PopID();

	return TRUE;
}

void ComponentUI::RemoveComponent()
{
	bool failed = false;
	if (ImGui::Button("Remove"))
		ImGui::OpenPopup("Remove Component");
	if (ImGui::BeginPopupModal("Remove Component", NULL))
	{
		ImGui::Text("Really want to remove this Component?");

		if (ImGui::Button("Yes"))
		{
			if (GetTarget()->DeleteComponent(this->GetComponentType()) == FALSE)
			{
				ImGui::OpenPopup("Failed Remove Component");
			}
		}
		bool unused_open = true;
		if (ImGui::BeginPopupModal("Failed Remove Component", &unused_open))
		{
			ImGui::Text("You can't delete this Component");
			if (ImGui::Button("Close"))
			{
				failed = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (failed)
			ImGui::CloseCurrentPopup();
		ImGui::SameLine();
		if (ImGui::Button("No"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

void ComponentUI::SetTarget(CGameObject* _Target)
{
	m_Target = _Target;

	if (nullptr == m_Target)
	{
		SetActive(false);
		return;
	}

	if (nullptr == m_Target->GetComponent(m_Type))
	{
		SetActive(false);
	}
	else
	{
		SetActive(true);
	}
}

void ComponentUI::GetResKey(Ptr<CRes> _Res, char* _Buff, size_t _BufferSize)
{
	memset(_Buff, 0, sizeof(char) * _BufferSize);

	if (nullptr == _Res)			
		return;	

	wstring wstrKey = _Res->GetKey();
	string	strKey = string(wstrKey.begin(), wstrKey.end());
	memcpy(_Buff, strKey.data(), sizeof(char) * strKey.length());
}