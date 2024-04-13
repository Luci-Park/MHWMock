#pragma once
#include "AnjStruct.h"
#include "AnjAction.h"
class CAnjanath;
class AnjActionPicker
{
private:
	AnjAction* m_Actions[(int)ANJ_ACTION::NONE];
	CAnjanath* m_pParent;
	ANJ_ACTION m_prevAction;
public:
	AnjAction* PickAction(ANJ_ACTION _action = ANJ_ACTION::NONE);

public:
	AnjActionPicker(CAnjanath* _parent);
	~AnjActionPicker();
};

