#include "pch.h"
#include "CollisionUI.h"

#include "TreeUI.h"
#include "ImGuiMgr.h"
#include "InspectorUI.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CCollisionMgr.h>

CollisionUI::CollisionUI()
	: UI("##Collision")
{
	SetName("Collision");
}

CollisionUI::~CollisionUI()
{
    for (int i = 0; i < (MAX_LAYER + 1) * (MAX_LAYER + 1); ++i)
    {
        delete m_pLabel[i];
        m_pLabel[i] = nullptr;
    }
}


void CollisionUI::init()
{
    //const char* label = std::to_string(cell).c_str();
    for (int i = 0; i < (MAX_LAYER + 1) * (MAX_LAYER + 1); ++i)
    {
        int len1 = strlen("##");
        int len2 = strlen(std::to_string(i).c_str());

        m_pLabel[i] = new char[len1 + len2 + 1];
        
        strcpy(m_pLabel[i], "##");
        strcat(m_pLabel[i], std::to_string(i).c_str());
    }
}

void CollisionUI::tick()
{
    UI::tick();
}

int CollisionUI::render_update()
{
    ImGuiStyle& style = ImGui::GetStyle();

    //const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    const float TEXT_BASE_HEIGHT = ImGui::CalcTextSize("A").y * 2.0f;
    const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;


    // ImGui::TreeNode("Horizontal scrolling");
    // ImGui::TreePop();
    // ImGui::TextUnformatted()  :   문자열 그대로 표시
    // ImGui::SameLine();
    // ImGui::Spacing();    :   사이 간격
 
    ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * MAX_LAYER);
    static float inner_width = 2000.0f;
    static ImGuiTableFlags flags2 = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));        ImGui::PushID("flags3");
    //ImGui::PushItemWidth(TEXT_BASE_WIDTH * 30);
    ImGui::PushItemWidth(TEXT_BASE_WIDTH);
    //ImGui::CheckboxFlags("ImGuiTableFlags_ScrollX", &flags2, ImGuiTableFlags_ScrollX);
    //ImGui::DragFloat("inner_width", &inner_width, 1.0f, 0.0f, FLT_MAX, "%.1f");
    ImGui::PopItemWidth();
    ImGui::PopID();
    ImGui::PopStyleVar(2);

    // 레벨 매니저에서 현재 레밸 받아옴.
    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

    for (UINT row = 0; row < MAX_LAYER; ++row)
    {
        for (UINT col = 0; col < MAX_LAYER; ++col)
        {
            m_bCollisionMap[row][col] = CCollisionMgr::GetInst()->GetCollisionMap(row, col);
        }
    }

    if (ImGui::BeginTable("CollisionTable", MAX_LAYER + 1, flags2, outer_size, inner_width))
    {
        for (int cell = 0; cell < (MAX_LAYER + 1) * (MAX_LAYER + 1); ++cell)
        {
            ImGui::TableNextColumn();

            // 첫번째 행    :   LayerNum
            if (ImGui::TableGetRowIndex() == 0)
            {
                if (ImGui::TableGetColumnIndex() == 0)
                {
                    ImGui::Text("");
                    continue;
                }
                ImGui::TextUnformatted(ToString((LAYER_TYPE)(MAX_LAYER - ImGui::TableGetColumnIndex())));
                continue;
            }

            // 첫번재 열    :   LayerName
            if (ImGui::TableGetColumnIndex() == 0)
            {
                ImGui::TextUnformatted(ToString((LAYER_TYPE)(ImGui::TableGetRowIndex() - 1)));
                continue;
            }

            // Cutting
            if (ImGui::TableGetColumnIndex() > (MAX_LAYER + 1) - ImGui::TableGetRowIndex())
            {
                continue;
            }

         

            ImGui::Checkbox(m_pLabel[cell], &m_bCollisionMap[ImGui::TableGetRowIndex() - 1][MAX_LAYER - ImGui::TableGetColumnIndex()]);
            ImGui::Text("%d, %d", ImGui::TableGetRowIndex() - 1, MAX_LAYER - ImGui::TableGetColumnIndex());
        }
        ImGui::EndTable();
    }
  
    for (UINT row = 0; row < MAX_LAYER; ++row)
    {
        for (UINT col = 0; col < MAX_LAYER; ++col)
        {
            CCollisionMgr::GetInst()->SetCollisionMap(row, col, m_bCollisionMap[row][col]);
        }
    }

    //static ImGuiTableFlags flags = ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
    //static int freeze_cols = 1;
    //static int freeze_rows = 1;
    //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
    //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
    //ImGui::CheckboxFlags("ImGuiTableFlags_ScrollX", &flags, ImGuiTableFlags_ScrollX);
    //ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
    //ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
    //ImGui::DragInt("freeze_cols", &freeze_cols, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
    //ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
    //ImGui::DragInt("freeze_rows", &freeze_rows, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
    //ImGui::PopStyleVar(2);
    //
    ////When using ScrollX or ScrollY we need to specify a size for our table container!
    ////Otherwise by default the table will fit all available space, like a BeginChild() call.
    //if (ImGui::BeginTable("table_scrollx", 7, flags, outer_size))
    //{
    //    ImGui::TableSetupScrollFreeze(freeze_cols, freeze_rows);
    //    ImGui::TableSetupColumn("Line #", ImGuiTableColumnFlags_NoHide); // Make the first column not hideable to match our use of TableSetupScrollFreeze()
    //    ImGui::TableSetupColumn("One");
    //    ImGui::TableSetupColumn("Two");
    //    ImGui::TableSetupColumn("Three");
    //    ImGui::TableSetupColumn("Four");
    //    ImGui::TableSetupColumn("Five");
    //    ImGui::TableSetupColumn("Six");
    //    ImGui::TableHeadersRow();
    //    for (int row = 0; row < 20; row++)
    //    {
    //        ImGui::TableNextRow();
    //        for (int column = 0; column < 7; column++)
    //        {
    //            // Both TableNextColumn() and TableSetColumnIndex() return true when a column is visible or performing width measurement.
    //            // Because here we know that:
    //            // - A) all our columns are contributing the same to row height
    //            // - B) column 0 is always visible,
    //            // We only always submit this one column and can skip others.
    //            // More advanced per-column clipping behaviors may benefit from polling the status flags via TableGetColumnFlags().
    //            if (!ImGui::TableSetColumnIndex(column) && column > 0)
    //                continue;
    //            if (column == 0)
    //                ImGui::Text("Line %d", row);
    //            else
    //                ImGui::Text("Hello world %d,%d", column, row);
    //        }
    //    }
    //    ImGui::EndTable();
    //}
    
    
     
    
    //ImVec2 button_sz(40, 40);
    //ImGui::Button("A", button_sz); ImGui::SameLine();
    //ImGui::Dummy(button_sz); ImGui::SameLine();
    //ImGui::Button("B", button_sz);

    //ImGui::Text("Manual wrapping:");
    //int buttons_count = 20;
    //float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
    //for (int n = 0; n < buttons_count; n++)
    //{
    //    ImGui::PushID(n);
    //    ImGui::Button("Box", button_sz);
    //    float last_button_x2 = ImGui::GetItemRectMax().x;
    //    float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; 
    //    if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
    //        ImGui::SameLine();
    //    ImGui::PopID();
    //}





    //static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

    //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
    //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));
    //ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
    //ImGui::PopStyleVar(2);

    //// When using ScrollX or ScrollY we need to specify a size for our table container!
    //// Otherwise by default the table will fit all available space, like a BeginChild() call.
    //ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
    //if (ImGui::BeginTable("table_scrolly", 3, flags, outer_size))
    //{
    //    ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
    //    ImGui::TableSetupColumn("One", ImGuiTableColumnFlags_None);
    //    ImGui::TableSetupColumn("Two", ImGuiTableColumnFlags_None);
    //    ImGui::TableSetupColumn("Three", ImGuiTableColumnFlags_None);
    //    ImGui::TableHeadersRow();

    //    // Demonstrate using clipper for large vertical lists
    //    ImGuiListClipper clipper;
    //    clipper.Begin(1000);
    //    while (clipper.Step())
    //    {
    //        for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
    //        {
    //            ImGui::TableNextRow();
    //            for (int column = 0; column < 3; column++)
    //            {
    //                ImGui::TableSetColumnIndex(column);
    //                ImGui::Text("Hello %d,%d", column, row);
    //            }
    //        }
    //    }
    //    ImGui::EndTable();
    //}

    return 0;
}

