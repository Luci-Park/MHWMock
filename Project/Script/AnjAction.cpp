#include "pch.h"
#include "AnjAction.h"

AnjAction::AnjAction(ANJ_ACTION _type, CAnjanath* _parent)
	: m_type(_type)
	, m_pParent(_parent)
{
}

AnjAction::~AnjAction()
{
}

