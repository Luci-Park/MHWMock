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
	void SetName(string _name);
	string GetClipName();
	void SetAnimation(Ptr<CAnimationClip> _clip);

	float GetSpeed() { return m_pState->GetSpeed(); }
	void SetSpeed(float _fSpeed) { m_pState->SetSpeed(_fSpeed); }
	Node(CAnimationState* _state);
};

struct Link
{

};