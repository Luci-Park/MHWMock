#pragma once
#include "AnjStruct.h"

class CMainPlayerScript;
class CAnjanath;
class AnjAction
{
private:
	ANJ_ACTION	m_type;
	const int	m_iAttackPower;
	bool		m_bAttacked;
	bool		m_bAttacking;

	CAnjanath*	m_pParent;
public:
	ANJ_ACTION GetType() { return m_type; }
	CAnjanath* Parent() { return m_pParent; }

	void OnAttack(SCRIPT_TYPE _type, CMainPlayerScript* _player);
	void AttackEnd() { m_bAttacked = false; }

	virtual bool Pickable() = 0;
	virtual REPOS_DIR TurnDir() = 0;
	virtual bool KeepMoving() = 0;

	virtual void OnAnimationStart(wstring _animationName);
	virtual void OnAnimationEnd(wstring _animationName);

protected:
	int AttackPower() { return m_iAttackPower; }
	virtual bool IsStartAnimation(wstring _animationName) = 0;
	virtual bool IsEndAnimation(wstring _animationName) = 0;
	virtual int CalculateDamage(SCRIPT_TYPE _type) = 0;
public:
	AnjAction(ANJ_ACTION _type, CAnjanath* _parent, int _atkPwr = 0);
	~AnjAction();
};

class Anj_Roar:
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();
	virtual void OnAnimationStart(wstring _animationName) override;

protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_Roar(CAnjanath* _parent);
	~Anj_Roar();
};

class Anj_Bite :
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();
	virtual void OnAnimationStart(wstring _animationName) override;

protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_Bite(CAnjanath* _parent);
	~Anj_Bite();
};

class Anj_ContinBite :
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();
	virtual void OnAnimationStart(wstring _animationName) override;

protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_ContinBite(CAnjanath* _parent);
	~Anj_ContinBite();
};

class Anj_ClawScratch :
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();

protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_ClawScratch(CAnjanath* _parent);
	~Anj_ClawScratch();
};

class Anj_TailSlam :
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();
protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_TailSlam(CAnjanath* _parent);
	~Anj_TailSlam();
};

class Anj_TailSweep :
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();
protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_TailSweep(CAnjanath* _parent);
	~Anj_TailSweep();
};

class Anj_BodySlam :
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();
protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_BodySlam(CAnjanath* _parent);
	~Anj_BodySlam();
};

class Anj_ForwardAtk :
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();
	virtual void OnAnimationStart(wstring _animationName) override;

protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_ForwardAtk(CAnjanath* _parent);
	~Anj_ForwardAtk();
};

class Anj_Rush :
	public AnjAction
{
private:

public:
	virtual bool Pickable();
	virtual REPOS_DIR TurnDir();
	virtual bool KeepMoving();
	virtual void OnAnimationStart(wstring _animationName) override;

protected:
	virtual bool IsStartAnimation(wstring _animationName) override;
	virtual bool IsEndAnimation(wstring _animationName) override;
	virtual int CalculateDamage(SCRIPT_TYPE _type) override;

public:
	Anj_Rush(CAnjanath* _parent);
	~Anj_Rush();
};