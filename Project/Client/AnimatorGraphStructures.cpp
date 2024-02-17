#include "pch.h"
#include "AnimatorGraphStructures.h"

string Node::GetName()
{
	return WSTR2STR(m_pState->GetName());
}

void Node::SetName(string _name)
{
	m_pState->SetName(STR2WSTR(_name));
}

string Node::GetClipName()
{
	auto anim = m_pState->GetClip();
	if (nullptr == anim)
		return "";
	else
		return WSTR2STR(anim->GetKey());
}

void Node::SetAnimation(Ptr<CAnimationClip> _clip)
{
	m_pState->SetClip(_clip);
}

Node::Node(CAnimationState* _state)
	: m_pState(_state)
	, id(ed::NodeId(_state))
{
}

Link::Link(CAnimationTransition* _transit)
	: m_pTransit(_transit)
	, id(ed::LinkId(_transit))
{
	string prevState = WSTR2STR(_transit->GetPrevState()->GetName());
	string nextState = WSTR2STR(_transit->GetNextState()->GetName());
	name = prevState + " -> " + nextState;
}
