#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 68532.f

Anj_TailSweep::Anj_TailSweep(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::TAIL_SWEEP, _parent)
{
}

Anj_TailSweep::~Anj_TailSweep()
{
}

bool Anj_TailSweep::Pickable()
{
	float distance = Parent()->GetDistanceBetweenPlayer();
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = DISTANCE * scale;

	return distance <= targetDistance;
}


REPOS_DIR Anj_TailSweep::TurnDir()
{
	return REPOS_DIR::NONE;
}

bool Anj_TailSweep::KeepMoving()
{
	return false;
}

void Anj_TailSweep::CheckAnimation(wstring _animationName)
{
}



