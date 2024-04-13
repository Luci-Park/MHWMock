#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 351760.f

Anj_Rush::Anj_Rush(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::RUSH, _parent, 60)
{
}

Anj_Rush::~Anj_Rush()
{
}

bool Anj_Rush::Pickable()
{
	return true;
}


REPOS_DIR Anj_Rush::TurnDir()
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

bool Anj_Rush::KeepMoving()
{
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = DISTANCE * scale;

	return Parent()->GetDistanceBetweenPlayer() > targetDistance;
}

void Anj_Rush::OnAnimationStart(wstring _animationName)
{
	AnjAction::OnAnimationStart(_animationName);
	if (IsStartAnimation(_animationName))
		Parent()->LookAtPlayer();
}

bool Anj_Rush::IsStartAnimation(wstring _animationName)
{
	return _animationName == L"Animation 144";
}

bool Anj_Rush::IsEndAnimation(wstring _animationName)
{
	return _animationName == L"Animation 146";
}

int Anj_Rush::CalculateDamage(SCRIPT_TYPE _type)
{
	return AttackPower();
}



