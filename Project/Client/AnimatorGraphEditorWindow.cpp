#include "pch.h"
#include "AnimatorGraphEditorWindow.h"

AnimatorGraphEditorWindow::AnimatorGraphEditorWindow(CAnimator3D* _animator)
	: m_pAnimator(_animator)
{
	OnStart();
}

AnimatorGraphEditorWindow::~AnimatorGraphEditorWindow()
{
	OnEnd();
}

void AnimatorGraphEditorWindow::OnDraw()
{
}

void AnimatorGraphEditorWindow::OnStart()
{
	m_pEditor = ed::CreateEditor();
	ed::SetCurrentEditor(m_pEditor);
}

void AnimatorGraphEditorWindow::OnEnd()
{
	if (m_pEditor)
	{
		ed::DestroyEditor(m_pEditor);
		m_pEditor = nullptr;
	}
}
