#pragma once
#include "CMainPlayerScript.h"
#include "AnjStruct.h"
class CAnjanath;
class AnjAttack
{
private:
	ANJ_ATTACK m_type;
	CAnjanath* m_pParent;
	int m_iAttackPower;
	bool m_bAttacked;
	bool m_bDidStartDir;
public:
	ANJ_ATTACK GetType() { return m_type; }

	virtual bool Attackable() = 0;
	void AttackStart();
	virtual void AttackTick() = 0;
	void AttackEnd();

	void AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player);
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart()override;
	virtual void OnAttackEnd() override;
public:
	WeakBite(CAnjanath* _parent);
	virtual ~WeakBite();
};

class Bite : public AnjAttack
{
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
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
public:
	virtual bool Attackable() override;
	virtual void AttackTick() override;
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart);
	virtual void OnAttackStart();
	virtual void OnAttackEnd();
public:
	Flame(CAnjanath* _parent);
	virtual ~Flame();
};