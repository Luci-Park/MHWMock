#pragma once
enum class ANJ_ATTACK
{
	WEAK_BITE, BITE, CONTIN_BITE, CLAW, TAIL_SLAM, TAIL_SWEEP, BODY_SLAM, FORWARD, RUSH, FLAME
};
class AnjAttack
{
public:
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart) = 0;

public:
	AnjAttack();
	virtual ~AnjAttack();
};

