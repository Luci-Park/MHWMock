#pragma once
#include "CMainPlayerScript.h"
enum class ANJ_ATTACK
{
	WEAK_BITE, BITE, CONTIN_BITE, CLAW, TAIL_SLAM, TAIL_SWEEP, BODY_SLAM, FORWARD, RUSH, FLAME
};

class CAnjanath;
class AnjAttack
{
private:
	ANJ_ATTACK m_type;
	CAnjanath* m_pParent;
	int m_iAttackPower;
	bool m_bAttacked;
public:
	ANJ_ATTACK GetType() { return m_type; }

	void AttackStart();
	void AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player);
	void AttackEnd();
protected:
	int AttackPower() { return m_iAttackPower; }
	CAnjanath* Parent() { return m_pParent; }

	virtual int DamageContribution(SCRIPT_TYPE _attackPart) = 0;
	virtual void OnAttackStart() = 0;
	virtual void OnAttackEnd() = 0;


public:
	AnjAttack(ANJ_ATTACK _type, CAnjanath* _parent, int _power);
	virtual ~AnjAttack();
};

class WeakBite : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	WeakBite(CAnjanath* _parent);
	virtual ~WeakBite();
};

class Bite : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	Bite(CAnjanath* _parent);
	virtual ~Bite();
};

class ContinBite : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	ContinBite(CAnjanath* _parent);
	virtual ~ContinBite();
};

class Claw : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	Claw(CAnjanath* _parent);
	virtual ~Claw();
};


class TailSlam : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	TailSlam(CAnjanath* _parent);
	virtual ~TailSlam();
};

class TailSweep : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	TailSweep(CAnjanath* _parent);
	virtual ~TailSweep();
};

class BodySlam : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	BodySlam(CAnjanath* _parent);
	virtual ~BodySlam();
};

class ForwardAtk : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	ForwardAtk(CAnjanath* _parent);
	virtual ~ForwardAtk();
};

class Rush : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	Rush(CAnjanath* _parent);
	virtual ~Rush();
};

class Flame : public AnjAttack
{
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	Flame(CAnjanath* _parent);
	virtual ~Flame();
};