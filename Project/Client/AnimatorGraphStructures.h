#pragma once
#include "ImGui/imgui_node_editor.h"
#include <Engine/CAnimationStateMachine.h>
namespace ed = ax::NodeEditor;

struct Node;
struct Pin
{
	ed::PinId	id;
	ed::PinKind type;
	Node*		node;
};

struct Node
{
public:
	ed::NodeId id;
	CAnimationState* m_pState;
public:
	string GetName();
	Node(CAnimationState* _state);
};

struct Link
{

};