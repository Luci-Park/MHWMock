#include "Animator3DUI.h"

bool GraphEditorDelegate::AllowedLink(NodeIndex from, NodeIndex to)
{
    return false;
}

void GraphEditorDelegate::SelectNode(NodeIndex nodeIndex, bool selected)
{
}

void GraphEditorDelegate::MoveSelectedNodes(const ImVec2 delta)
{
}

void GraphEditorDelegate::AddLink(NodeIndex inputNodeIndex, SlotIndex inputSlotIndex, NodeIndex outputNodeIndex, SlotIndex outputSlotIndex)
{
}

void GraphEditorDelegate::DelLink(LinkIndex linkIndex)
{
}

void GraphEditorDelegate::CustomDraw(ImDrawList* drawList, ImRect rectangle, NodeIndex nodeIndex)
{
}

void GraphEditorDelegate::RightClick(NodeIndex nodeIndex, SlotIndex slotIndexInput, SlotIndex slotIndexOutput)
{
}

const size_t GraphEditorDelegate::GetTemplateCount()
{
    return size_t();
}

const Template GraphEditorDelegate::GetTemplate(TemplateIndex index)
{
    return Template();
}

const size_t GraphEditorDelegate::GetNodeCount()
{
    return size_t();
}

const Node GraphEditorDelegate::GetNode(NodeIndex index)
{
    return Node();
}

const size_t GraphEditorDelegate::GetLinkCount()
{
    return size_t();
}

const Link GraphEditorDelegate::GetLink(LinkIndex index)
{
    return Link();
}
