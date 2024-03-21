#include "pch.h"
#define IMGUI_DEFINE_MATH_OPERATORS

#include "AnimatorGraphEditorWindow.h"
#include "AnimatorGraphStructures.h"
#include <Engine/CAnimationState.h>
#include <Engine/CAnimationStateMachine.h>

#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_stdlib.h"
#include "ImGuiFunc.h"


AnimatorGraphEditorWindow::AnimatorGraphEditorWindow(CAnimator3D* _animator
	, CAnimationStateMachine* _targetMachine, ed::EditorContext* _parentContext)
	: m_iCurrentEditingParam(-1)
	, m_fLeftPlaneWidth(200.f)
	, m_fRightPlaneWidth(800.f)
	, m_pAnimator(_animator)
	, m_iCurrSelectedAnimationIdx(-1)
	, m_pStateMachine(_targetMachine)
{
	string filename = "Animator.json";
	ed::Config config;
	config.SettingsFile = filename.c_str();
	m_pEditor = ed::CreateEditor(&config);
	
	ed::SetCurrentEditor(m_pEditor);
	ed::NavigateToContent();

	HashState states = m_pStateMachine->GetAllStates();
	for (auto s : states)
	{
		Node newNode = CreateNode(s);
		Vec2 pos = s->GetViewNode().vPos;
		ed::SetNodePosition(newNode.id, ImVec2(pos.x, pos.y));
	}

	for (auto s : states)
	{
		HashTransition transitions = s->GetAllTransitions();
		for (auto t : transitions)
		{
			auto linkInfo = t->GetViewLink();
			auto prevNode = GetNode(ed::NodeId(t->GetPrevState()));
			auto nextNode = GetNode(ed::NodeId(t->GetNextState()));
			m_Links.emplace_back(t, &(*prevNode).outputPins[0], 
				&(*nextNode).inputPins[0]);
		}
	}
	ed::SetCurrentEditor(_parentContext);
}

AnimatorGraphEditorWindow::AnimatorGraphEditorWindow(CAnimator3D* _animator)
	:AnimatorGraphEditorWindow(_animator, _animator->GetStateMachine())
{
}

AnimatorGraphEditorWindow::~AnimatorGraphEditorWindow()
{
	if (m_pEditor)
	{
		ed::DestroyEditor(m_pEditor);
		m_pEditor = nullptr;
	}
	for (auto i : m_SubWindows)
		delete i.second;
}

Node& AnimatorGraphEditorWindow::CreateNode(eAnimationNodeType _type)
{
	IAnimationState* pNewState;
	if (_type == eAnimationNodeType::StateMachine) pNewState = m_pStateMachine->CreateSubStateMachine();
	else pNewState = m_pStateMachine->CreateState();
	m_pStateMachine->Reset(0);
	return CreateNode(pNewState);
}

Node& AnimatorGraphEditorWindow::CreateNode(IAnimationState* _state)
{
	if (eAnimationNodeType::StateMachine == _state->GetType())
	{
		auto newWindow = new AnimatorGraphEditorWindow(m_pAnimator, (CAnimationStateMachine*)_state, m_pEditor);
		m_SubWindows.insert(make_pair((CAnimationStateMachine*)_state, newWindow));
	}
	m_Nodes.emplace_back(_state);
	return m_Nodes.back();
}

Link& AnimatorGraphEditorWindow::CreateTransition(const Pin* _startPin, const Pin* _endPin)
{
	IAnimationState* prevState = _startPin->node->pState;
	IAnimationState* nextState = _endPin->node->pState;
	CAnimationTransition* transition = new CAnimationTransition(prevState, nextState, m_pStateMachine);
	m_pStateMachine->Reset(0);
	m_Links.emplace_back(transition, _startPin, _endPin);
	return m_Links.back();
}

void AnimatorGraphEditorWindow::DeleteNode(ed::NodeId _node)
{
	auto iter = GetNode(_node);	
	if (iter->pAnimMachine != nullptr)
	{
		auto it = m_SubWindows.find(iter->pAnimMachine);
		if (it != m_SubWindows.end())
		{
			delete it->second;
			m_SubWindows.erase(it);
		}
	}
	m_pStateMachine->DeleteState(iter->pState);
	m_Nodes.erase(iter);
}

void AnimatorGraphEditorWindow::DeleteLink(ed::LinkId _link)
{
	auto iter = GetLink(_link);
	iter->pTransit->Remove();
	m_Links.erase(iter);
}


void AnimatorGraphEditorWindow::OnFrame(ed::EditorContext* _parentContext)
{
	string windowName = WSTR2STR(m_pStateMachine->GetName()) + "##Animator" + std::to_string((uintptr_t)(void**)this);
	ImGui::Begin(windowName.c_str());

	ed::SetCurrentEditor(m_pEditor);
	Splitter(true, 4.0f, &m_fLeftPlaneWidth, &m_fRightPlaneWidth, 50.0f, 50.0f, 0);
	ShowLeftPanel(m_fLeftPlaneWidth - 4.0f);
	ImGui::SameLine(0.0f, 12.0f);

	ed::Begin("Node Editor");

	for (auto n : m_Nodes)
		DrawNode(n);
	for (auto l : m_Links)
		ed::Link(l.id, l.startPin->id, l.endPin->id);
	if (ed::BeginCreate(ImColor(255, 255, 255), 2.0f))
	{
		auto showLabel = [](const char* label, ImColor color)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetTextLineHeight());
			auto size = ImGui::CalcTextSize(label);

			auto padding = ImGui::GetStyle().FramePadding;
			auto spacing = ImGui::GetStyle().ItemSpacing;

			ImGui::SetCursorPos(ImGui::GetCursorPos() + ImVec2(spacing.x, -spacing.y));

			auto rectMin = ImGui::GetCursorScreenPos() - padding;
			auto rectMax = ImGui::GetCursorScreenPos() + size + padding;

			auto drawList = ImGui::GetWindowDrawList();
			drawList->AddRectFilled(rectMin, rectMax, color, size.y * 0.15f);
			ImGui::TextUnformatted(label);
		}; 
		ed::PinId startPinId = 0, endPinId = 0;
		if (ed::QueryNewLink(&startPinId, &endPinId))
		{
			auto startPin = GetPin(startPinId);
			auto endPin = GetPin(endPinId);

			if (startPin && endPin)
			{
				if (startPin->kind == ed::PinKind::Input)
				{
					std::swap(startPin, endPin);
					std::swap(startPinId, endPinId);
				}
				if (startPin == endPin)
				{
					ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
				}
				else if (endPin->node == startPin->node)
				{
					showLabel("x Cannot connect to self", ImColor(45, 32, 32, 180));
					ed::RejectNewItem(ImColor(255, 0, 0), 1.0f);
				}
				else if (endPin->kind == startPin->kind)
				{
					showLabel("x Incompatible Pin Kind", ImColor(45, 32, 32, 180));
					ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
				}
				else
				{
					showLabel("+ Create Link", ImColor(32, 45, 32, 180));
					if (ed::AcceptNewItem(ImColor(128, 255, 128), 4.0f))
					{
						Link newLink = CreateTransition(startPin, endPin);
						ed::Link(newLink.id, newLink.startPin->id, newLink.endPin->id);

					}
				}
			}
		}
	}
	ed::EndCreate();
	
	if (ed::BeginDelete())
	{
		ed::NodeId nodeId;
		while (ed::QueryDeletedNode(&nodeId))
		{
			if (ed::AcceptDeletedItem())
				DeleteNode(nodeId);
		}
		ed::LinkId linkId;
		while (ed::QueryDeletedLink(&linkId))
		{
			if (ed::AcceptDeletedItem())
				DeleteLink(linkId);
		}
	}
	ed::EndDelete();
	DealWithPopup();
	SavePosition();
	ed::End();

	ed::SetCurrentEditor(_parentContext);
	ImGui::End();
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
		{
			m_currSelectedLink = link;
			ImGui::OpenPopup("Link Context Menu");
		}
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
				ed::DeleteLink(m_currSelectedLink);
			ImGui::EndPopup();
		}

		if (ImGui::BeginPopup("Background Context Menu"))
		{
			if (ImGui::MenuItem("Create State"))
			{
				Node newNode = CreateNode(eAnimationNodeType::State);
				ed::SetNodePosition(newNode.id, clickPos);
			}
			if (ImGui::MenuItem("Create Sub State Machine"))
			{
				Node newNode = CreateNode(eAnimationNodeType::StateMachine);
				ed::SetNodePosition(newNode.id, clickPos);
			}
			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();
	}
	ed::Resume();
}

void AnimatorGraphEditorWindow::DrawNode(Node& _node)
{
	float rounding = _node.pAnimState != nullptr ? 12.0f : 0.f;
	const float padding = 12.0f;
	const auto pinBackground = ed::GetStyle().Colors[ed::StyleColor_NodeBg];
	ImColor color = _node.pState == m_pStateMachine->GetHead() ?
		ImColor(191, 108, 26, 200) : ImColor(72, 74, 77, 200);

	ed::PushStyleColor(ed::StyleColor_NodeBg, color);
	ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(32, 32, 32, 200));
	ed::PushStyleColor(ed::StyleColor_PinRect, ImColor(60, 180, 255, 150));
	ed::PushStyleColor(ed::StyleColor_PinRectBorder, ImColor(60, 180, 255, 150));

	ed::PushStyleVar(ed::StyleVar_NodePadding, ImVec4(0, 0, 0, 0));
	ed::PushStyleVar(ed::StyleVar_NodeRounding, rounding);
	ed::PushStyleVar(ed::StyleVar_SourceDirection, ImVec2(0.0f, 1.0f));
	ed::PushStyleVar(ed::StyleVar_TargetDirection, ImVec2(0.0f, -1.0f));
	ed::PushStyleVar(ed::StyleVar_LinkStrength, 0.0f);

	ed::BeginNode(_node.id);


	const ImVec2 nodeSize(200, 40);
	float sizeY = nodeSize.y;
	{
		ed::PushStyleVar(ed::StyleVar_PinArrowSize, 10.0f);
		ed::PushStyleVar(ed::StyleVar_PinArrowWidth, 10.0f);
		ed::BeginPin(_node.inputPins[0].id, ed::PinKind::Input);
		ImGui::Dummy(ImVec2(nodeSize.x * 0.5, 10));
		ed::EndPin();
		ed::PopStyleVar(2);

		ImGui::SameLine(0, 0);
		
		ed::BeginPin(_node.outputPins[0].id, ed::PinKind::Output);
		ImGui::Dummy(ImVec2(nodeSize.x * 0.5, 10));
		ed::EndPin();
		sizeY -= 10;
	}
	BeginColumn();
	float pinSizeY = sizeY;
	ed::PushStyleVar(ed::StyleVar_PinArrowSize, 10.0f);
	ed::PushStyleVar(ed::StyleVar_PinArrowWidth, 10.0f);
	ed::BeginPin(_node.inputPins[1].id, ed::PinKind::Input);
	ImGui::Dummy(ImVec2(10, pinSizeY * 0.5));
	ed::EndPin();
	ed::PopStyleVar(2);

	ed::BeginPin(_node.outputPins[1].id, ed::PinKind::Output);
	ImGui::Dummy(ImVec2(10, pinSizeY * 0.5));
	ed::EndPin();
	NextColumn();
	{
		auto textSize = ImGui::CalcTextSize(_node.GetName().c_str());
		ImGui::Dummy(ImVec2(nodeSize.x - 20, nodeSize.y * 0.05)); sizeY -= nodeSize.y * 0.05;
		ImGui::Dummy(ImVec2((nodeSize.x - textSize.x - 20) * 0.5, 0));
		ImGui::SameLine(0, 0);
		ImGui::Text(_node.GetName().c_str()); sizeY -= textSize.y;
		if (_node.pAnimState != nullptr && _node.pAnimState->GetTickPercent() > 0)
		{
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, Convert255To1(51, 133, 190));
			ImGui::Dummy(ImVec2(nodeSize.x * 0.02, textSize.y * 1.2)); ImGui::SameLine(0, 0);
			ImGui::ProgressBar(_node.pAnimState->GetTickPercent(), ImVec2(nodeSize.x - 30, textSize.y * 1.2));
			ImGui::PopStyleColor();
			sizeY -= textSize.y * 1.2;
		}
	}
	NextColumn();

	ed::PushStyleVar(ed::StyleVar_PinArrowSize, 10.0f);
	ed::PushStyleVar(ed::StyleVar_PinArrowWidth, 10.0f);
	ed::BeginPin(_node.inputPins[2].id, ed::PinKind::Input);
	ImGui::Dummy(ImVec2(10, pinSizeY * 0.5));
	ed::EndPin();
	ed::PopStyleVar(2);
	
	ed::BeginPin(_node.outputPins[2].id, ed::PinKind::Output);
	ImGui::Dummy(ImVec2(10, pinSizeY * 0.5));
	ed::EndPin();
	EndColumn();


	ed::PushStyleVar(ed::StyleVar_PinArrowSize, 10.0f);
	ed::PushStyleVar(ed::StyleVar_PinArrowWidth, 10.0f);
	ImGui::Dummy(ImVec2(0, sizeY - 10));
	ed::BeginPin(_node.inputPins[3].id, ed::PinKind::Input);
	ImGui::Dummy(ImVec2(nodeSize.x * 0.5, 10));
	ed::EndPin();
	ed::PopStyleVar(2);

	ImGui::SameLine(0, 0);
	
	ed::BeginPin(_node.outputPins[3].id, ed::PinKind::Output);
	ImGui::Dummy(ImVec2(nodeSize.x * 0.5, 10));
	ed::EndPin();

	ed::EndNode();

	ed::PopStyleVar(5);
	ed::PopStyleColor(4);
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

	auto node = GetNode(*selectedNode);
	auto link = GetLink(*selectedLink);
	if (node != m_Nodes.end())
	{
		if (m_pSelectedNode != nullptr
			&& node->id != m_pSelectedNode->id) 
			m_pSelectedTransition = nullptr;
		m_pSelectedNode = &(*node);
		DrawSelection(*node);
	}
	if (link != m_Links.end())
	{
		DrawSelection(*link);
	}

	ImGui::EndChild();
}

void AnimatorGraphEditorWindow::DrawSelection(Node& _node)
{
	float width = ImGui::GetContentRegionAvail().x;

	string name = _node.GetName();
	ImGui::InputText("##StateName", &name, ImGuiInputTextFlags_EnterReturnsTrue);
	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
	{
		_node.SetName(name);
	}
	ImGui::Separator();
	if (_node.pAnimState != nullptr)
	{
#pragma region Set Clip
		ImGui::Text("Animation");
		ImGui::SameLine();
		string clipName = _node.GetClipName();
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
			if (ImGui::Selectable("(null)"))
			{
				_node.pAnimState->SetClip(nullptr);
				ImGui::CloseCurrentPopup();
			}
			else
			{
				vector<wstring>& names = m_pAnimator->GetAnimNames();
				for (int i = 0; i < names.size(); i++)
				{
					if (ImGui::Selectable(WSTR2STR(names[i]).c_str()))
					{
						_node.pAnimState->SetClip(m_pAnimator->GetAnimation(names[i]));
						ImGui::CloseCurrentPopup();
						break;
					}
				}
			}
			ImGui::EndPopup();
		}

#pragma endregion
#pragma region Clip Settings
		ImGui::Text("Speed    ");
		ImGui::SameLine();
		ImGui::PushItemWidth(120);
		float speed = _node.pAnimState->GetSpeed();
		ImGui::DragFloat("##SpeedFloat", &speed, 0.1, 0, 3.0);
		_node.pAnimState->SetSpeed(speed);
		ImGui::PopItemWidth();

#pragma endregion
	}
	else
	{
		auto iter = m_SubWindows.find(_node.pAnimMachine);
		assert(iter != m_SubWindows.end());
		iter->second->OnFrame(m_pEditor);
	}
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
	HashTransition& transits = _node.pState->GetAllTransitions();
	for (auto t : transits)
	{
		ed::LinkId id(t);
		auto link = GetLink(id);
		if (ImGui::MenuItem(link->name.c_str()))
			m_pSelectedTransition = &(*link);

	}
	ImGui::Separator();
	if (m_pSelectedTransition != nullptr)
		DrawSelection(*m_pSelectedTransition);

	ImGui::EndChild();
	ImGui::PopStyleVar();
#pragma endregion


}

void AnimatorGraphEditorWindow::DrawSelection(Link& _link)
{
	ImGui::Text(_link.name.c_str());
	ImGui::Separator();
#pragma region Transition Settings
	bool	bHasExit =			_link.pTransit->GetHasExitTime();
	float	fExitTime =			_link.pTransit->GetExitTime();
	bool	bFixedDur =			_link.pTransit->GetFixedDuration();
	float	fTransitionDur =	_link.pTransit->GetTransitionDuration();
	float	fTransitionOffset =	_link.pTransit->GetTransitionOffset();

	ImGui::Text("Has Exit Time ");
	ImGui::SameLine();
	ImGui::Checkbox("##ExitTimeBool", &bHasExit); 

	ImGui::Text("Exit Time     ");
	ImGui::SameLine();
	ImGui::DragFloat("##ExitTimeFloat", &fExitTime);

	ImGui::Text("Fixed Duration");
	ImGui::SameLine();
	ImGui::Checkbox("##FixedDurationBool", &bFixedDur);

	ImGui::Text("Duration      ");
	ImGui::SameLine();
	ImGui::DragFloat("##DurationFloat", &fTransitionDur);

	ImGui::Text("Offset        ");
	ImGui::SameLine();
	ImGui::DragFloat("##OffsetFloat", &fTransitionOffset);
	
	_link.pTransit->SetHasExitTime(bHasExit);
	_link.pTransit->SetExitTime(fExitTime);
	_link.pTransit->SetFixedDuration(bFixedDur);
	_link.pTransit->SetTransitionDuration(fTransitionDur);
	_link.pTransit->SetTransitionOffset(fTransitionOffset);
	
	vector<AnimCondition*> conditions = _link.pTransit->GetAllConditions();
	if (conditions.size() == 0) _link.pTransit->SetHasExitTime(true);
#pragma endregion
#pragma region Parameter Settings
	ImGui::TextUnformatted("Conditions");
	ImGui::Separator();

	if (ImGui::Button("Create Condition"))
	{
		_link.pTransit->CreateCondition();
	}

	vector<AnimStateParam*> params = m_pStateMachine->GetAllParams();
	for (int i = 0; i < conditions.size(); i++)
	{
		AnimCondition* cond = conditions[i];
		ImGui::PushID(cond);
		float size = ImGui::GetContentRegionAvail().x;
		ImGui::PushItemWidth(size * 0.33f);
		if (ImGui::BeginCombo("##SelectParam", WSTR2STR(cond->lhs->name).c_str()))
		{
			for (int j = 0; j < params.size(); j++)
			{
				ImGui::PushID((void*)params[j]);
				if (ImGui::Selectable(WSTR2STR(params[j]->name).c_str(), cond->lhs == params[j]))
					_link.pTransit->ChangeConditionParam(cond, params[j]);
				ImGui::PopID();
			}
			ImGui::EndCombo();
		}
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			ImGui::OpenPopup("##DeleteCondition");
		if (AnimParamType::FLOAT == cond->lhs->type)
		{
			ImGui::SameLine();
			if (ImGui::BeginCombo("##ParamExpression", GetAnimConditionStr(cond->expr).c_str()))
			{
				for (int j = 0; j < (UINT)AnimConditionType::NONE; j++)
				{
					AnimConditionType type = (AnimConditionType)j;
					if (type != AnimConditionType::GREATER && type != AnimConditionType::LESS) continue;
					if (ImGui::Selectable(GetAnimConditionStr(type).c_str(), cond->expr == type))
						cond->expr = type;
				}
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			ImGui::DragFloat("##FloatParam", &cond->rhs);
		}
		if (AnimParamType::INT == cond->lhs->type)
		{
			ImGui::SameLine();
			if (ImGui::BeginCombo("##ParamExpression", GetAnimConditionStr(cond->expr).c_str()))
			{
				for (int j = 0; j < (UINT)AnimConditionType::NONE; j++)
				{
					AnimConditionType type = (AnimConditionType)j;
					if (type != AnimConditionType::GREATER && type != AnimConditionType::LESS
						&& type != AnimConditionType::EQUAL && type != AnimConditionType::NOTEQUAL) continue;
					if (ImGui::Selectable(GetAnimConditionStr(type).c_str(), cond->expr == type))
						cond->expr = type;
				}
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			int num = cond->rhs;
			ImGui::DragInt("##IntParam", &num);
			cond->rhs = num;
		}
		if (AnimParamType::BOOL == cond->lhs->type)
		{
			ImGui::SameLine();
			if (ImGui::BeginCombo("##ParamExpression", GetAnimConditionStr(cond->expr).c_str()))
			{
				for (int j = 0; j < (UINT)AnimConditionType::NONE; j++)
				{
					AnimConditionType type = (AnimConditionType)j;
					if (type != AnimConditionType::ISFALSE && type != AnimConditionType::ISTRUE) continue;
					if (ImGui::Selectable(GetAnimConditionStr(type).c_str(), cond->expr == type))
						cond->expr = type;
				}
				ImGui::EndCombo();
			}
		}

		if (ImGui::IsPopupOpen("##DeleteCondition"))
		{
			if (ImGui::MenuItem("Delete##ConditionDelete"))
			{
				_link.pTransit->DeleteCondition(i);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::IsKeyPressed(ImGuiKey_Delete)) ImGui::CloseCurrentPopup();
		}

		ImGui::PopItemWidth();
		ImGui::PopID();
	}
#pragma endregion
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
		float semiWidth = _width * 0.3;
		float indent = semiWidth - ImGui::CalcTextSize(name.c_str()).x;
		ImGui::SameLine(semiWidth);
		if (AnimParamType::FLOAT == params[i]->type)
			ImGui::DragFloat("##inputfloat", &(params[i]->value.FLOAT));
		if (AnimParamType::INT == params[i]->type)
			ImGui::DragInt("##inputint", &(params[i]->value.INT));
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
				m_pStateMachine->SetParamName(params[i], STR2WSTR(name));
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
	if (!_id) return m_Nodes.end();
	for (auto it = m_Nodes.begin(); it != m_Nodes.end(); ++it) {
		if (it->id == _id) {
			return it;
		}
	}
	return m_Nodes.end();
}

list<Link>::iterator AnimatorGraphEditorWindow::GetLink(ed::LinkId _id)
{
	if (!_id) return m_Links.end();
	for (auto it = m_Links.begin(); it != m_Links.end(); ++it) {
		if (it->id == _id) {
			return it;
		}
	}
	return m_Links.end();
}

const Pin* AnimatorGraphEditorWindow::GetPin(ed::PinId _id)
{
	for (auto it = m_Nodes.begin(); it != m_Nodes.end(); ++it)
	{
		auto pin = it->PinExists(_id);
		if (pin) return pin;
	}
	return nullptr;
}

void AnimatorGraphEditorWindow::BeginColumn()
{
	ImGui::BeginGroup();
}

void AnimatorGraphEditorWindow::NextColumn()
{
	ImGui::EndGroup();
	ImGui::SameLine(0, 0);
	ImGui::BeginGroup();
}

void AnimatorGraphEditorWindow::EndColumn()
{
	ImGui::EndGroup();
}

void AnimatorGraphEditorWindow::SavePosition()
{
	for (auto n : m_Nodes)
	{
		tAnimationStateNode info;
		ImVec2 pos = ed::GetNodePosition(n.id);
		info.vPos = Vec2(pos.x, pos.y);
		n.pState->UpdatePos(info);
	}
	for (auto l : m_Links)
	{
		tAnimationTransitionLink info;
		info.startIdx = l.startPin->idx;
		info.endIdx = l.endPin->idx;
		l.pTransit->UpdateLink(info);
	}
}