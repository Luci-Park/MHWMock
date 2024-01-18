#pragma once
#include "ResUI.h"
class ModelUI :
	public ResUI
{
public:
	virtual int render_update() override;
public:
	ModelUI();
	~ModelUI();
};

