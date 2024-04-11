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
	virtual bool KeepMoving() = 0;
	virtual REPOS_DIR TurnDir() = 0;

public:
	AnjAction(ANJ_ACTION _type, CAnjanath* _parent);
	~AnjAction();
};

class Anj_Roar:
	public AnjAction
{
	virtual bool Pickable();
	virtual bool KeepMoving();
	virtual REPOS_DIR TurnDir();
public:
	Anj_Roar(CAnjanath* _parent);
	~Anj_Roar();
};