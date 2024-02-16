#include "pch.h"
#include "AnimatorGraphStructures.h"

string Node::GetName()
{
	return WSTR2STR(m_pState->GetName());
}

Node::Node(CAnimationState* _state)
	: m_pState(_state)
	, id(ed::NodeId(_state))
{
}
