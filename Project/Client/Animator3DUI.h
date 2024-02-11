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
    virtual bool AllowedLink(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to);

    virtual void SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected);
    virtual void MoveSelectedNodes(const ImVec2 delta);

    virtual void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex, GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex);
    virtual void DelLink(GraphEditor::LinkIndex linkIndex);

    // user is responsible for clipping
    virtual void CustomDraw(ImDrawList* drawList, ImRect rectangle, GraphEditor::NodeIndex nodeIndex);

    // use mouse position to open context menu
    // if nodeIndex != -1, right click happens on the specified node
    virtual void RightClick(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex slotIndexInput, GraphEditor::SlotIndex slotIndexOutput);

    virtual const size_t GetTemplateCount();
    virtual const GraphEditor::Template GetTemplate(GraphEditor::TemplateIndex index);

    virtual const size_t GetNodeCount();
    virtual const GraphEditor::Node GetNode(GraphEditor::NodeIndex index);

    virtual const size_t GetLinkCount();
    virtual const GraphEditor::Link GetLink(GraphEditor::LinkIndex index);
};
