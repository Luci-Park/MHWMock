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

int AnimatorGraphEditorWindow::OnDraw()
{
	ed::NodeId contextNodeId = 0;
	ed::LinkId contextLinkId = 0;
	ed::PinId  contextPinId = 0;
	ed::SetCurrentEditor(m_pEditor);
	ed::Begin("Node Editor");
	{

	}
	{
		auto openPopupPosition = ImGui::GetMousePos();
		ed::Suspend();
		if (ed::ShowNodeContextMenu(&contextNodeId))
			ImGui::OpenPopup("Node Context Menu");
		else if (ed::ShowPinContextMenu(&contextPinId))
			ImGui::OpenPopup("Pin Context Menu");
		else if (ed::ShowLinkContextMenu(&contextLinkId))
			ImGui::OpenPopup("Link Context Menu");
		else if (ed::ShowBackgroundContextMenu())
		{
			ImGui::OpenPopup("Create New Node");
			//newNodeLinkPin = nullptr;
		}
		ed::Resume();
	}
	ed::End();
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
