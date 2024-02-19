#pragma once
#include "ImGui/imgui_node_editor.h"
#include <Engine/CAnimationStateMachine.h>
namespace ed = ax::NodeEditor;

struct Node;
struct Pin
{
	friend class Node;
	ed::PinId	id;
	int			idx;
	Node*		node;
private:
	Pin(int _id, int _idx, Node* _node);
	Pin();
};

struct Node
{
private:
	static int PINID;
public:
	ed::NodeId			id;
	CAnimationState*	pState;
	const Pin			inputPins[4];
	const Pin			outputPins[4];

	string	GetName();
	void	SetName(string _name);
	string	GetClipName();
	void	SetAnimation(Ptr<CAnimationClip> _clip);

	float	GetSpeed() { return pState->GetSpeed(); }
	void	SetSpeed(float _fSpeed) { pState->SetSpeed(_fSpeed); }

	const Pin* PinExists(ed::PinId _pinId, ed::PinKind _pinType);

	Node(CAnimationState* _state);
};

struct Link
{
	ed::LinkId				id;
	const Pin*				inputPin;
	const Pin*				outputPin;

	CAnimationTransition*	pTransit;
	string					name;

	Link(CAnimationTransition* _transit);
};