#include "pch.h"
#include "BoneHolderUI.h"

BoneHolderUI::BoneHolderUI()
	:ComponentUI("##BoneHolder", COMPONENT_TYPE::BONEHOLDER)
{
	SetName("BoneHolder");
}

BoneHolderUI::~BoneHolderUI()
{
}
int BoneHolderUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;
	return 0;
}

