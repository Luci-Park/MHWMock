#include "AnjAction.h"


Anj_Roar::Anj_Roar(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::ROAR, _parent)
{
}

Anj_Roar::~Anj_Roar()
{
}

bool Anj_Roar::Pickable()
{
	return false;
}

bool Anj_Roar::KeepMoving()
{
	return false;
}

REPOS_DIR Anj_Roar::TurnDir()
{
	return REPOS_DIR();
}
