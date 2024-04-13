#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 187635.f

Anj_ForwardAtk::Anj_ForwardAtk(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::FORWARD_ATK, _parent)
{
}

Anj_ForwardAtk::~Anj_ForwardAtk()
{
}

bool Anj_ForwardAtk::Pickable()
{	
	return true;
}


REPOS_DIR Anj_ForwardAtk::TurnDir()
{
	float angle = Parent()->GetAngleBetweenPlayer();
	float distance = Parent()->GetDistanceBetweenPlayer();
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = DISTANCE * scale;

	if (distance <= targetDistance * 0.25f)
	{
		if (abs(angle) <= 90) return REPOS_DIR::FRONT;
		return REPOS_DIR::VRYNEAR;
	}

	if (distance <= targetDistance)
	{
		if (abs(angle) < 45.f) return REPOS_DIR::FRONT;
		if (abs(angle) < 135.f) return angle < 0 ? REPOS_DIR::LEFT : REPOS_DIR::RIGHT;
		return REPOS_DIR::LEFTBACK; //angle < 0 ? REPOS_DIR::LEFTBACK : REPOS_DIR::RIGHTBACK;
	}

	if (abs(angle) < 45.f) return REPOS_DIR::NONE;
	if (abs(angle) < 135.f) return angle < 0 ? REPOS_DIR::FARLEFT : REPOS_DIR::FARRIGHT;
	return angle < 0 ? REPOS_DIR::FARLEFTBACK : REPOS_DIR::FARRIGHTBACK;
}

bool Anj_ForwardAtk::KeepMoving()
{
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = DISTANCE * scale;

	return Parent()->GetDistanceBetweenPlayer() > targetDistance;
}

void Anj_ForwardAtk::CheckAnimation(wstring _animationName)
{
	if (_animationName == L"Animation 222.002")
		Parent()->LookAtPlayer();
}



