#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#include <Engine/CTransform.h>

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

REPOS_DIR Anj_Roar::TurnDir()
{
	float angle = Parent()->GetAngleBetweenPlayer();
	float distance = Parent()->GetDistanceBetweenPlayer();
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = 2000.f * scale;

	if (distance <= targetDistance && abs(angle) <= 135.f)  return REPOS_DIR::VRYNEAR;

	if (abs(angle) < 45.f) return REPOS_DIR::FRONT;
	if (abs(angle) < 135.f) return angle < 0 ? REPOS_DIR::LEFT : REPOS_DIR::RIGHT;
	return REPOS_DIR::LEFTBACK;//angle < 0 ? REPOS_DIR::LEFTBACK : REPOS_DIR::RIGHTBACK;

}

bool Anj_Roar::KeepMoving()
{
	return false;
}

void Anj_Roar::OnAnimationStart(wstring _animationName)
{
	AnjAction::OnAnimationStart(_animationName);
	if(IsStartAnimation(_animationName))
		Parent()->LookAtPlayer();
}

int Anj_Roar::CalculateDamage(SCRIPT_TYPE _type)
{
	return 0;
}

bool Anj_Roar::IsStartAnimation(wstring _animationName)
{
	return _animationName == L"Animation 001.002";
}

bool Anj_Roar::IsEndAnimation(wstring _animationName)
{
	return _animationName == L"Animation 001.002";
}
