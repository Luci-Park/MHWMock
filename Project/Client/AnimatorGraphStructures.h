#pragma once
#include "ImGui/imgui_node_editor.h"
#include <Engine/IAnimationState.h>
#define NUMBEROFPINS 4
namespace ed = ax::NodeEditor;

class CAnimationState;
class CAnimationStateMachine;
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
	ed::NodeId				id;
	IAnimationState*		pState;
	CAnimationState*		pAnimState;
	CAnimationStateMachine* pAnimMachine;
	const Pin				inputPins[NUMBEROFPINS];
	const Pin				outputPins[NUMBEROFPINS];

	string	GetName();
	void	SetName(string _name);
	void	SetName(wstring _name);
	string	GetClipName();

	const Pin* PinExists(ed::PinId _pinId);

	Node(IAnimationState* _state);
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