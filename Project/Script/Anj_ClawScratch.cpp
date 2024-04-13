#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#define DISTANCE 36648.f

Anj_ClawScratch::Anj_ClawScratch(CAnjanath* _parent)
	: AnjAction(ANJ_ACTION::CLAW_SCRATCH, _parent, 20)
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

bool Anj_ClawScratch::IsStartAnimation(wstring _animationName)
{
	return _animationName == L"Animation 178.002";
}

bool Anj_ClawScratch::IsEndAnimation(wstring _animationName)
{
	return _animationName == L"Animation 178.002";
}

int Anj_ClawScratch::CalculateDamage(SCRIPT_TYPE _type)
{
	if (_type != SCRIPT_TYPE::ANJANATHLEFTLEG) return 0;
	return AttackPower();
}



