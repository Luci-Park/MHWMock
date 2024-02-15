#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_node_editor.h"
#include <Engine/CAnimator3D.h>

namespace ed = ax::NodeEditor;

struct Node
{

};

class AnimatorGraphEditorWindow
{
private:
	CAnimator3D* m_pAnimator;
	ed::EditorContext* m_pEditor;
public:
	virtual int OnDraw();
private:
	void OnStart();
	void OnEnd();
	
public:
	AnimatorGraphEditorWindow(CAnimator3D* _animator);
	~AnimatorGraphEditorWindow();
};

