#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 113800.f

Anj_ContinBite::Anj_ContinBite(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::CONTIN_BITE, _parent, 55)
{
}

Anj_ContinBite::~Anj_ContinBite()
{
}

bool Anj_ContinBite::Pickable()
{
	return true;
}


REPOS_DIR Anj_ContinBite::TurnDir()
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

bool Anj_ContinBite::KeepMoving()
{
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = DISTANCE * scale;

	return Parent()->GetDistanceBetweenPlayer() > targetDistance;
}

void Anj_ContinBite::OnAnimationStart(wstring _animationName)
{
	AnjAction::OnAnimationStart(_animationName);
	if(IsStartAnimation(_animationName))
		Parent()->LookAtPlayer();
}

int Anj_ContinBite::CalculateDamage(SCRIPT_TYPE _type)
{
	if (_type != SCRIPT_TYPE::ANJANATHHEAD) return 0;
	return AttackPower();
}


bool Anj_ContinBite::IsStartAnimation(wstring _animationName)
{
	return _animationName == L"Animation 030";
}

bool Anj_ContinBite::IsEndAnimation(wstring _animationName)
{
	return _animationName == L"Animation 030";
}

