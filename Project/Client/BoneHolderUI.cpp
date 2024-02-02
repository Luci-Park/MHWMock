#include "pch.h"
#include "BoneHolderUI.h"

int BoneHolderUI::render_update()
{
	return 0;
}

BoneHolderUI::BoneHolderUI()
	:ComponentUI("##BoneHolderUI", COMPONENT_TYPE::BONEHOLDER)
{
	SetName("BoneHolder");
}

BoneHolderUI::~BoneHolderUI()
{
}
