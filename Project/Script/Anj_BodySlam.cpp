#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 54731

Anj_BodySlam::Anj_BodySlam(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::BITE, _parent)
{
}

Anj_BodySlam::~Anj_BodySlam()
{
}

bool Anj_BodySlam::Pickable()
{
	float angle = Parent()->GetAngleBetweenPlayer();
	float distance = Parent()->GetDistanceBetweenPlayer();
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = DISTANCE * scale;

	return angle < 0 && distance <= targetDistance;
}


REPOS_DIR Anj_BodySlam::TurnDir()
{
	return REPOS_DIR::NONE;
}

bool Anj_BodySlam::KeepMoving()
{
	return false;
}

void Anj_BodySlam::CheckAnimation(wstring _animationName)
{
}



