#include "pch.h"
#include "CanvasUI.h"

CanvasUI::CanvasUI()
	: ComponentUI("##CANVAS",COMPONENT_TYPE::CANVAS)
{
	SetName("CANVAS");
}

CanvasUI::~CanvasUI()
{
}

int CanvasUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;

	ImGui::Text("Test");
	

	return TRUE;
}