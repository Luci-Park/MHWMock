#pragma once
#include "ImGui/imgui_node_editor.h"
#include <Engine/CAnimationStateMachine.h>
#define NUMBEROFPINS 4
namespace ed = ax::NodeEditor;

struct Node;
struct Pin
{
	friend class Node;
	ed::PinId	id;
	ed::PinKind kind;
	int			idx;
	Node*		node;
private:
	Pin(int _id, int _idx, ed::PinKind _kind, Node* _node);
	Pin();
};

struct Node
{
private:
	static int PINID;
public:
	ed::NodeId			id;
	CAnimationState*	pState;
	const Pin			inputPins[NUMBEROFPINS];
	const Pin			outputPins[NUMBEROFPINS];

	string	GetName();
	void	SetName(string _name);
	string	GetClipName();
	void	SetAnimation(Ptr<CAnimationClip> _clip);

	float	GetSpeed() { return pState->GetSpeed(); }
	void	SetSpeed(float _fSpeed) { pState->SetSpeed(_fSpeed); }

	const Pin* PinExists(ed::PinId _pinId);

	Node(CAnimationState* _state);
};

struct Link
{
	ed::LinkId				id;
	const Pin*				startPin;
	const Pin*				endPin;

	CAnimationTransition*	pTransit;
	string					name;

	Link(CAnimationTransition* _transit, const Pin* _startPin, const Pin* _endPin);
};