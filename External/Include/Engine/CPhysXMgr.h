#pragma once
#include "CSingleton.h"

class CPhysXMgr : public CSingleton<CPhysXMgr>
{
private:

public:
	void init();

public:
	CPhysXMgr();
	~CPhysXMgr();
};

