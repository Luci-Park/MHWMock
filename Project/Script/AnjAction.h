#pragma once
#include "AnjStruct.h"

class CAnjanath;
class AnjAction
{
private:
	ANJ_ACTION	m_type;
	const int	m_iAttackPower;
	bool		m_bAttacked;

	CAnjanath*	m_pParent;
public:
	ANJ_ACTION GetType() { return m_type; }
	CAnjanath* Parent() { return m_pParent; }
	virtual bool Pickable() = 0;
	virtual REPOS_DIR TurnDir() = 0;
	virtual bool KeepMoving() = 0;
	virtual void CheckAnimation(wstring _animationName) = 0;

public:
	AnjAction(ANJ_ACTION _type, CAnjanath* _parent);
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
	virtual void CheckAnimation(wstring _animationName);
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
	virtual void CheckAnimation(wstring _animationName);
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
	virtual void CheckAnimation(wstring _animationName);
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
	virtual void CheckAnimation(wstring _animationName);
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
	virtual void CheckAnimation(wstring _animationName);
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
	virtual void CheckAnimation(wstring _animationName);
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
	virtual void CheckAnimation(wstring _animationName);
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
	virtual void CheckAnimation(wstring _animationName);
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
	virtual void CheckAnimation(wstring _animationName);
public:
	Anj_Rush(CAnjanath* _parent);
	~Anj_Rush();
};