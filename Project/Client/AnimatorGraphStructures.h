#pragma once
#include "ImGui/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

struct Node
{
private:
	static int PinNum;
public:
	ed::NodeId id;
	ed::PinId inputPin;
	ed::PinId outputPin;
	Node();
};

struct Link
{

};