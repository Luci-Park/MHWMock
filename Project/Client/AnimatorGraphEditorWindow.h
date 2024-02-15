#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_node_editor.h"
#include <Engine/CAnimator3D.h>
#include <Engine/CAnimationStateMachine.h>

namespace ed = ax::NodeEditor;

struct Node
{

};

class AnimatorGraphEditorWindow
{
private:
	CAnimationStateMachine* m_pAnimator;
	ed::EditorContext* m_pEditor;

	float m_fLeftPlaneWidth = 200.0f;
	float m_fRightPlaneWidth = 800.0f;
	int m_iCurrentEditingParam;
public:
	virtual void OnDraw();
private:
	void OnStart();
	void OnEnd();
	void ShowLeftPanel(float _width);
	void ShowSelection(float _width, float _height);
	void DrawSelection(ed::NodeId* _node);
	void DrawSelection(ed::LinkId* _link);
	void ShowParamConfigPanel(float _width, float _height);
	bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, int _id, float splitter_long_axis_size = -1.0f);
public:
	AnimatorGraphEditorWindow(CAnimator3D* _animator);
	~AnimatorGraphEditorWindow();
};

