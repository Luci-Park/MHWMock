#pragma once
#include "ComponentUI.h"
#include "ImGui/GraphEditor.h"

class Animator3DUI :
	public ComponentUI
{
private:
	void Gizmo();
public:
	virtual int render_update() override;
public:
	Animator3DUI();
	~Animator3DUI();
};

struct GraphEditorDelegate : public GraphEditor::Delegate
{

};
