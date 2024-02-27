#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_node_editor.h"
#include <Engine/CAnimationStateMachine.h>
namespace ed = ax::NodeEditor;

class CAnimator3D;
struct Node;
struct Link;
struct Pin;

class AnimatorGraphEditorWindow
{
private:
	CAnimationStateMachine*		m_pStateMachine;
	CAnimator3D*				m_pAnimator;
	ed::EditorContext*			m_pEditor;

	list<Node>					m_Nodes;
	list<Link>					m_Links;

	ed::NodeId					m_currSelectedNode;
	ed::LinkId					m_currSelectedLink;
	int							m_iCurrSelectedAnimationIdx;
	Link*						m_pSelectedTransition;
	Node*						m_pSelectedNode;
	
	float						m_fLeftPlaneWidth;
	float						m_fRightPlaneWidth;
	int							m_iCurrentEditingParam; //idx of currently name editing param
public:
	virtual void OnFrame();
private:
	void OnStart();
	void OnEnd();
	void DrawNode(Node& _node);
	void DealWithPopup();
	void ShowLeftPanel(float _width);
	void ShowSelection(float _width, float _height);
	void DrawSelection(Node& _node);
	void DrawSelection(Link& _link);
	void ShowParamConfigPanel(float _width, float _height);	
	bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, int _id, float splitter_long_axis_size = -1.0f);
private:
	Node& CreateNode(CAnimationState* _state);
	Node& CreateNode();
	void DeleteNode(ed::NodeId _node);

	Link& CreateTransition(const Pin* _startPin, const Pin* _endPin);

	void DeleteLink(ed::LinkId _link);

	list<Node>::iterator GetNode(ed::NodeId _id);
	list<Link>::iterator GetLink(ed::LinkId _id);
	const Pin* GetPin(ed::PinId _id);

	void BeginColumn();
	void NextColumn();
	void EndColumn();

	void SavePosition();
public:
	AnimatorGraphEditorWindow(CAnimator3D* _animator);
	~AnimatorGraphEditorWindow();
};

