#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 68532.f

Anj_TailSweep::Anj_TailSweep(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::TAIL_SWEEP, _parent, 35)
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

bool Anj_TailSweep::IsStartAnimation(wstring _animationName)
{
	return _animationName == L"Animation 047.002";
}

bool Anj_TailSweep::IsEndAnimation(wstring _animationName)
{
	return _animationName == L"Animation 047.002";
}

int Anj_TailSweep::CalculateDamage(SCRIPT_TYPE _type)
{
	if (_type != SCRIPT_TYPE::ANJANATHTAIL) return 0;
	return AttackPower();
}



