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

bool Anj_Roar::KeepMoving()
{
	return false;
}

REPOS_DIR Anj_Roar::TurnDir()
{
	float angle = Parent()->GetAngleBetweenPlayer();
	float distance = Parent()->GetDistanceBetweenPlayer();
	float scale = Parent()->Transform()->GetWorldScale().x;

	if (distance <= (2000.f * scale) && abs(angle) <= -135.f)  return REPOS_DIR::VRYNEAR;

	if (abs(angle) < 45.f) return REPOS_DIR::FRONT;
	if (abs(angle) < 135.f) return angle < 0 ? REPOS_DIR::LEFT : REPOS_DIR::RIGHT;
	return angle < 0 ? REPOS_DIR::LEFTBACK : REPOS_DIR::RIGHTBACK;

}

void Anj_Roar::CheckAnimation(wstring _animationName)
{
	if (_animationName == L"Animation 001.002")
		Parent()->LookAtPlayer();
}
