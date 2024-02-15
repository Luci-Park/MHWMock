#include "pch.h"
#define IMGUI_DEFINE_MATH_OPERATORS

#include "AnimatorGraphEditorWindow.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_stdlib.h"
#include <Engine/func.h>
#include <Engine/CKeyMgr.h>
AnimatorGraphEditorWindow::AnimatorGraphEditorWindow(CAnimator3D* _animator)
	: m_iCurrentEditingParam(-1)
{
	m_pAnimator = _animator->GetStateMachine();
	OnStart();
}

AnimatorGraphEditorWindow::~AnimatorGraphEditorWindow()
{
	OnEnd();
}

void AnimatorGraphEditorWindow::OnDraw()
{
	ed::NodeId contextNodeId = 0;
	ed::LinkId contextLinkId = 0;
	ed::PinId  contextPinId = 0;
	ed::SetCurrentEditor(m_pEditor);
	Splitter(true, 4.0f, &m_fLeftPlaneWidth, &m_fRightPlaneWidth, 50.0f, 50.0f, 0);
	ShowLeftPanel(m_fLeftPlaneWidth - 4.0f);

	ImGui::SameLine(0.0f, 12.0f);
	ed::Begin("Node Editor");
	{

	}
	{
		auto openPopupPosition = ImGui::GetMousePos();
		ed::Suspend();
		if (ed::ShowNodeContextMenu(&contextNodeId))
			ImGui::OpenPopup("Node Context Menu");
		else if (ed::ShowPinContextMenu(&contextPinId))
			ImGui::OpenPopup("Pin Context Menu");
		else if (ed::ShowLinkContextMenu(&contextLinkId))
			ImGui::OpenPopup("Link Context Menu");
		else if (ed::ShowBackgroundContextMenu())
		{
			ImGui::OpenPopup("Create New Node");
			//newNodeLinkPin = nullptr;
		}
		ed::Resume();
	}
	ed::End();
}

void AnimatorGraphEditorWindow::ShowLeftPanel(float _width)
{
	ImGui::BeginChild("Left Panel", ImVec2(_width, 0), false, ImGuiWindowFlags_NoScrollbar);
	float fullHeight = ImGui::GetContentRegionAvail().y;
	float halfHeight1 = fullHeight * 0.5f;
	float halfHeight2 = fullHeight * 0.5f;
	Splitter(false, 4.0f, &halfHeight1, &halfHeight2, 50.0f, 50.0f, 0);
	ShowSelection(_width, halfHeight1 - 5.2f);
	ImGui::Dummy(ImVec2(0, 5.f));
	ShowParamConfigPanel(_width, halfHeight2 - 5.2f);

	ImGui::EndChild();
}

void AnimatorGraphEditorWindow::ShowSelection(float _width, float _height)
{
	ImGui::BeginChild("Selection", ImVec2(_width, _height));
	_width = ImGui::GetContentRegionAvail().x;

#pragma region Header
	ImGui::GetWindowDrawList()->AddRectFilled(
		ImGui::GetCursorScreenPos(),
		ImGui::GetCursorScreenPos() + ImVec2(_width, ImGui::GetTextLineHeight() * 1.3),
		ImColor(ImGui::GetStyle().Colors[ImGuiCol_HeaderActive]), ImGui::GetTextLineHeight() * 0.25f);
	ImGui::Spacing(); ImGui::SameLine();
	ImGui::TextUnformatted("Selection");
	ImGui::Dummy(ImVec2(0, 2.f));
	ImGui::Separator();
#pragma endregion

	int i = 4;
	while (i--)
	{
		ImGui::Text("Test");
	}
	ImGui::EndChild();
}

void AnimatorGraphEditorWindow::ShowParamConfigPanel(float _width, float _height)
{
	ImGui::BeginChild("Params", ImVec2(_width, _height));
	_width = ImGui::GetContentRegionAvail().x;

#pragma region Header
	ImGui::GetWindowDrawList()->AddRectFilled(
		ImGui::GetCursorScreenPos(),
		ImGui::GetCursorScreenPos() + ImVec2(_width, ImGui::GetTextLineHeight() * 1.3),
		ImColor(ImGui::GetStyle().Colors[ImGuiCol_HeaderActive]), ImGui::GetTextLineHeight() * 0.25f);
	ImGui::Spacing(); ImGui::SameLine();
	ImGui::TextUnformatted("Params");
	ImGui::Dummy(ImVec2(0, 2.f));
	ImGui::Separator();
#pragma endregion

	if (ImGui::Button("Add Param"))
	{
		ImGui::OpenPopup("##ParamTypePopup");
	}
	if (ImGui::BeginPopup("##ParamTypePopup"))
	{
		AnimParamType type = AnimParamType::NONE;
		if (ImGui::MenuItem("float"))
			type = AnimParamType::FLOAT;
		if (ImGui::MenuItem("int"))
			type = AnimParamType::INT;
		if (ImGui::MenuItem("bool"))
			type = AnimParamType::BOOL;
		if (ImGui::MenuItem("trigger"))
			type = AnimParamType::TRIGGER;
		m_pAnimator->CreateNewParam(type);
		ImGui::EndPopup();
	}

	vector<AnimStateParam*>& params = m_pAnimator->GetAllParams();

	for (int i = 0; i < params.size(); i++)
	{
		ImGui::PushID(params[i]);
		string name = WSTR2STR(params[i]->name);
# if IMGUI_VERSION_NUM >= 18967
			ImGui::SetNextItemAllowOverlap();
# endif
		if (ImGui::Selectable(name.c_str()))
		{
			if (m_iCurrentEditingParam == i)
				m_iCurrentEditingParam = -1;
			else
				m_iCurrentEditingParam = i;

		}

		if (ImGui::IsItemHovered() &&
			ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("##paramDeletePopup");
			m_iCurrentEditingParam = -1;
		}

		ImGui::SameLine();
		if (AnimParamType::FLOAT == params[i]->type)
			ImGui::InputFloat("##inputfloat", &(params[i]->value.FLOAT));
		if (AnimParamType::INT == params[i]->type)
			ImGui::InputInt("##inputint", &(params[i]->value.INT));
		if (AnimParamType::BOOL == params[i]->type)
			ImGui::Checkbox("##inputBool", &(params[i]->value.BOOL));
		if (AnimParamType::TRIGGER == params[i]->type)
			ImGui::Checkbox("##inputTrigger", &(params[i]->value.TRIGGER));

		if (ImGui::BeginPopup("##paramDeletePopup"))
		{
			if (ImGui::MenuItem("Delete##paramDelete"))
			{
				m_pAnimator->DeleteParam(i);
			}
			ImGui::EndPopup();
			ImGui::PopID();
			continue;
		}

		if (m_iCurrentEditingParam == i)
		{	
			ImGui::InputText("##NodeName", &name, ImGuiInputTextFlags_EnterReturnsTrue);
			if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
			{
				params[i]->name = STR2WSTR(name);
				m_iCurrentEditingParam = -1;
			}
			else if (ImGui::IsKeyPressed(ImGuiKey_Delete)
				|| ImGui::IsKeyPressed(ImGuiKey_Escape))
				m_iCurrentEditingParam = -1;
		}

		ImGui::PopID();
	}
	ImGui::EndChild();
}

void AnimatorGraphEditorWindow::OnStart()
{
	m_pEditor = ed::CreateEditor();
	ed::SetCurrentEditor(m_pEditor);
}

void AnimatorGraphEditorWindow::OnEnd()
{
	if (m_pEditor)
	{
		ed::DestroyEditor(m_pEditor);
		m_pEditor = nullptr;
	}
}



bool AnimatorGraphEditorWindow::Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, int _id, float splitter_long_axis_size)
{
	using namespace ImGui;
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	string name = "##Splitter" + std::to_string(_id);
	ImGuiID id = window->GetID(name.c_str());
	ImRect bb;
	bb.Min = window->DC.CursorPos + (split_vertically ? ImVec2(*size1, 0.0f) : ImVec2(0.0f, *size1));
	bb.Max = bb.Min + CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f);
	return SplitterBehavior(bb, id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 0.0f);
}
