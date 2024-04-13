#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 68532.f

Anj_TailSlam::Anj_TailSlam(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::TAIL_SLAM, _parent, 30)
{
}

Anj_TailSlam::~Anj_TailSlam()
{
}

bool Anj_TailSlam::Pickable()
{
	float angle = Parent()->GetAngleBetweenPlayer();
	float distance = Parent()->GetDistanceBetweenPlayer();
	float scale = Parent()->Transform()->GetWorldScale().x;
	float targetDistance = DISTANCE * scale;

	return abs(angle) < 140.f && distance <= targetDistance;
}


REPOS_DIR Anj_TailSlam::TurnDir()
{
	return REPOS_DIR::NONE;
}

bool Anj_TailSlam::KeepMoving()
{
	return false;
}

bool Anj_TailSlam::IsStartAnimation(wstring _animationName)
{
	return _animationName == L"Animation 003.003";
}

bool Anj_TailSlam::IsEndAnimation(wstring _animationName)
{
	return _animationName == L"Animation 003.003";
}

int Anj_TailSlam::CalculateDamage(SCRIPT_TYPE _type)
{
	if (_type != SCRIPT_TYPE::ANJANATHTAIL) return 0;
	return AttackPower();
}



