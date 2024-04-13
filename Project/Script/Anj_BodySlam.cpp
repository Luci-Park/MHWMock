#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 54731

Anj_BodySlam::Anj_BodySlam(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::BITE, _parent, 30)
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

bool Anj_BodySlam::IsStartAnimation(wstring _animationName)
{
	return _animationName == L"Animation 187.002";
}

bool Anj_BodySlam::IsEndAnimation(wstring _animationName)
{
	return _animationName == L"Animation 187.002";
}

int Anj_BodySlam::CalculateDamage(SCRIPT_TYPE _type)
{
	if (_type != SCRIPT_TYPE::ANJANATHBODY && _type != SCRIPT_TYPE::ANJANATHTAIL && _type != SCRIPT_TYPE::ANJANATHLEFTLEG) return 0;
	return AttackPower();
}



