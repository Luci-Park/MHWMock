#pragma once
#include "AnjStruct.h"

class CAnjanath;
class AnjAction
{
private:
	ANJ_ACTION m_type;
	CAnjanath* m_pParent;
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