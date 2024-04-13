#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 36648.f

Anj_ClawScratch::Anj_ClawScratch(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::CLAW_SCRATCH, _parent)
{
}

Anj_ClawScratch::~Anj_ClawScratch()
{
}

bool Anj_ClawScratch::Pickable()
{
	float angle = Parent()->GetAngleBetweenPlayer();
	float distance = Parent()->GetDistanceBetweenPlayer();
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = DISTANCE * scale;

	return abs(angle) < 140.f && distance <= targetDistance;
}


REPOS_DIR Anj_ClawScratch::TurnDir()
{
	return REPOS_DIR::NONE;
}

bool Anj_ClawScratch::KeepMoving()
{
	return false;
}

void Anj_ClawScratch::CheckAnimation(wstring _animationName)
{
}



