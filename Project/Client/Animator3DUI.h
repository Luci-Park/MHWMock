#pragma once
#include "ComponentUI.h"
#include "ImGui/GraphEditor.h"
#include "AnimatorGraphEditorWindow.h"

class Animator3DUI :
	public ComponentUI
{
private:
	map<CAnimator3D*, AnimatorGraphEditorWindow*> m_mapAnimator;
public:
	virtual int render_update() override;
public:
	Animator3DUI();
	~Animator3DUI();
};