#include "pch.h"
#include "AnimatorGraphStructures.h"

int Node::PINID = 0;

string Node::GetName()
{
	return WSTR2STR(pState->GetName());
}

void Node::SetName(string _name)
{
	pState->SetName(STR2WSTR(_name));
}

string Node::GetClipName()
{
	auto anim = pState->GetClip();
	if (nullptr == anim)
		return "";
	else
		return WSTR2STR(anim->GetKey());
}

void Node::SetAnimation(Ptr<CAnimationClip> _clip)
{
	pState->SetClip(_clip);
}

const Pin* Node::PinExists(ed::PinId _pinId)
{
	for (int i = 0; i < NUMBEROFPINS; i++)
	{
		if (outputPins[i].id == _pinId)
			return &outputPins[i];
		if (inputPins[i].id == _pinId)
			return &inputPins[i];
	}
	return nullptr;
}

Node::Node(CAnimationState* _state)
	: pState(_state)
	, id(ed::NodeId(_state))
	, inputPins{ {PINID++, 0, ed::PinKind::Input, this}, {PINID++, 1, ed::PinKind::Input, this}, {PINID++, 2, ed::PinKind::Input, this},{PINID++, 3, ed::PinKind::Input, this} }
	, outputPins{ {PINID++, 0, ed::PinKind::Output, this}, {PINID++, 1, ed::PinKind::Output, this}, {PINID++, 2, ed::PinKind::Output, this}, {PINID++, 3, ed::PinKind::Output, this} }
{
}

Link::Link(CAnimationTransition* _transit, const Pin* _startPin, const Pin* _endPin)
	: pTransit(_transit)
	, id(ed::LinkId(_transit))
	, startPin(_startPin)
	, endPin(_endPin)
{
	string prevState = WSTR2STR(_transit->GetPrevState()->GetName());
	string nextState = WSTR2STR(_transit->GetNextState()->GetName());
	name = prevState + " -> " + nextState;
}

Pin::Pin(int _id, int _idx, ed::PinKind _kind, Node* _node)
	: id(ed::PinId(_id)), idx(_idx), kind(_kind), node(_node)
{
}
