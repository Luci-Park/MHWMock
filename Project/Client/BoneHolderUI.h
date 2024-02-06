#pragma once
#include "ComponentUI.h"

class BoneHolderUI : 
	public ComponentUI
{
public:
	virtual int render_update() override;
public:
	BoneHolderUI();
	~BoneHolderUI();
};

