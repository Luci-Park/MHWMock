#include "pch.h"
#define IMGUI_DEFINE_MATH_OPERATORS

#include "AnimatorGraphEditorWindow.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_stdlib.h"
#include "ImGuiFunc.h"
#include "AnimatorGraphStructures.h"
#include "TreeUI.h"
#include <Engine/CKeyMgr.h>
#include <Engine/CResMgr.h>
#include "ListUI.h"

AnimatorGraphEditorWindow::AnimatorGraphEditorWindow(CAnimator3D* _animator)
	: m_iCurrentEditingParam(-1)
	, m_fLeftPlaneWidth(200.f)
	, m_fRightPlaneWidth(800.f)
	, m_pAnimator(_animator)
	, m_iCurrSelectedAnimationIdx(-1)
{
	OnStart();
	m_pStateMachine = _animator->GetStateMachine();
	HashState states = m_pStateMachine->GetAllStates();
	for (auto s : states)
	{
		Node newNode = CreateNode(s);
		ed::SetNodePosition(newNode.id, ImVec2(-20094.5781, 13565.7627));
	}
	ed::NavigateToContent();
}

AnimatorGraphEditorWindow::~AnimatorGraphEditorWindow()
{
	OnEnd();
}

Node& AnimatorGraphEditorWindow::CreateNode()
{
	CAnimationState* pNewState = m_pStateMachine->CreateState();
	return CreateNode(pNewState);
}

Node& AnimatorGraphEditorWindow::CreateNode(CAnimationState* _state)
{
	m_Nodes.emplace_back(_state);
	return m_Nodes.back();
}

void AnimatorGraphEditorWindow::DeleteNode(ed::NodeId _node)
{
	auto iter = GetNode(_node);	
	m_pStateMachine->DeleteState(iter->m_pState);
	m_Nodes.erase(iter);

}

void AnimatorGraphEditorWindow::OnDraw()
{
	ed::SetCurrentEditor(m_pEditor);
	Splitter(true, 4.0f, &m_fLeftPlaneWidth, &m_fRightPlaneWidth, 50.0f, 50.0f, 0);
	ShowLeftPanel(m_fLeftPlaneWidth - 4.0f);
	ImGui::SameLine(0.0f, 12.0f);

	ed::Begin("Node Editor");
	
	for (auto n : m_Nodes)
		DrawNode(n);
	if (ed::BeginDelete())
	{
		ed::NodeId nodeId;
		while (ed::QueryDeletedNode(&nodeId))
		{
			if (ed::AcceptDeletedItem())
				DeleteNode(nodeId);
		}
		ed::EndDelete();
	}
	DealWithPopup();
	
	ed::End();
	ed::SetCurrentEditor(nullptr);
}

void AnimatorGraphEditorWindow::DealWithPopup()
{
	ed::NodeId node;
	ed::PinId pin;
	ed::LinkId link;
	auto clickPos = ImGui::GetMousePos();
	ed::Suspend();
	{
		if (ed::ShowNodeContextMenu(&node))
		{
			m_currSelectedNode = node;
			ImGui::OpenPopup("Node Context Menu");
		}
		if (ed::ShowLinkContextMenu(&link))
			ImGui::OpenPopup("Link Context Menu");
		if (ed::ShowBackgroundContextMenu())
			ImGui::OpenPopup("Background Context Menu");
	}
	ed::Resume();

	ed::Suspend();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
		if (ImGui::BeginPopup("Node Context Menu"))
		{
			if (ImGui::MenuItem("Delete"))
				ed::DeleteNode(m_currSelectedNode);
			ImGui::EndPopup();
		}

		if (ImGui::BeginPopup("Link Context Menu"))
		{
			if (ImGui::MenuItem("Delete"))
				ed::DeleteLink(link);
			ImGui::EndPopup();
		}

		if (ImGui::BeginPopup("Background Context Menu"))
		{
			if (ImGui::MenuItem("Create State"))
			{
				Node newNode = CreateNode();
				ed::SetNodePosition(newNode.id, clickPos);
			}
			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();
	}
	ed::Resume();
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
	
	if (ed::GetSelectedObjectCount() <= 0)
	{
		ImGui::EndChild();
		return;
	}

	ed::NodeId selectedNode[1];
	ed::LinkId selectedLink[1];
	
	ed::GetSelectedNodes(selectedNode, 1);
	ed::GetSelectedLinks(selectedLink, 1);

	DrawSelection(selectedNode);
	DrawSelection(selectedLink);

	ImGui::EndChild();
}

void AnimatorGraphEditorWindow::DrawNode(Node& _node)
{
	const float rounding = 5.0f;
	const float padding = 12.0f;
	ImColor color = _node.m_pState == m_pStateMachine->GetHead() ?
		ImColor(191, 108, 26, 200) : ImColor(72, 74, 77, 200);
	ed::PushStyleColor(ed::StyleColor_NodeBg, color);
	ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(32, 32, 32));

	ed::PushStyleVar(ed::StyleVar_NodePadding, ImVec4(0, 0, 0, 0));
	ed::PushStyleVar(ed::StyleVar_NodeRounding, rounding);
	
	ed::BeginNode(_node.id);

	ImGui::Text(_node.GetName().c_str());
	if (_node.m_pState->GetTickPercent() > 0)
	{
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, Convert255To1(51, 133, 190));
		ImGui::ProgressBar(_node.m_pState->GetTickPercent(), ImVec2(0.0f, 0.0f));
		ImGui::PopStyleColor();
	}
	ed::EndNode();
	ed::PopStyleVar(2);
	ed::PopStyleColor(2);
}

void AnimatorGraphEditorWindow::DrawSelection(ed::NodeId* _node)
{
	float width = ImGui::GetContentRegionAvail().x;
	if (_node == nullptr)return;
	Node node = *GetNode(*_node);

	string name = node.GetName();
	ImGui::InputText("##StateName", &name, ImGuiInputTextFlags_EnterReturnsTrue);
	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
	{
		node.SetName(name);
	}
	ImGui::Separator();

#pragma region Set Clip
	ImGui::Text("Animation"); 
	ImGui::SameLine();
	string clipName = node.GetClipName();
	ImGui::PushItemWidth(100);
	ImGui::InputText("##AnimationName", &clipName, ImGuiInputTextFlags_ReadOnly);
	ImGui::PopItemWidth();

	ImGui::SameLine();

	if (ImGui::Button("##AnimSelectBtn", ImVec2(18, 18)))
	{
		ImGui::OpenPopup("##AnimationSelector");
	}
	if (ImGui::BeginPopup("##AnimationSelector"))
	{
		vector<wstring>& names = m_pAnimator->GetAnimNames();
		for (int i = 0; i < names.size(); i++)
		{
			if (ImGui::MenuItem(WSTR2STR(names[i]).c_str()))
			{
				node.SetAnimation(m_pAnimator->GetAnimation(names[i]));
				ImGui::CloseCurrentPopup();
				break;
			}
		}
		ImGui::EndPopup();
	}

#pragma endregion
#pragma region Clip Settings
	ImGui::Text("Speed    ");
	ImGui::SameLine();
	ImGui::PushItemWidth(120);
	float speed = node.GetSpeed();
	ImGui::DragFloat("##SpeedFloat", &speed, 0.1, 0, 3.0);
	node.SetSpeed(speed);
	ImGui::PopItemWidth();

#pragma endregion
#pragma region Transitions
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
	ImGui::BeginChild("Transition", ImVec2(width, 0), true);
	ImGui::GetWindowDrawList()->AddRectFilled(
		ImGui::GetCursorScreenPos(),
		ImGui::GetCursorScreenPos() + ImVec2(width, ImGui::GetTextLineHeight() * 1.3),
		ImColor(100, 100, 100)
		);
	ImGui::Spacing(); ImGui::SameLine();
	ImGui::TextUnformatted("Transitions");
	ImGui::Separator();

	ImGui::EndChild();
	ImGui::PopStyleVar();
#pragma endregion


}

void AnimatorGraphEditorWindow::DrawSelection(ed::LinkId* _link)
{
	if (_link == nullptr) return;
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
		m_pStateMachine->CreateNewParam(type);
		ImGui::EndPopup();
	}

	vector<AnimStateParam*>& params = m_pStateMachine->GetAllParams();

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
				m_pStateMachine->DeleteParam(i);
			}
			ImGui::EndPopup();
			ImGui::PopID();
			continue;
		}

		if (m_iCurrentEditingParam == i)
		{	
			ImGui::InputText("##ParamName", &name, ImGuiInputTextFlags_EnterReturnsTrue);
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

list<Node>::iterator AnimatorGraphEditorWindow::GetNode(ed::NodeId _id)
{
	for (auto it = m_Nodes.begin(); it != m_Nodes.end(); ++it) {
		if (it->id == _id) {
			return it;
		}
	}
	throw std::runtime_error("Node not found");
}

