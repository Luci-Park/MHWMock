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

    const float TEXT_BASE_HEIGHT = ImGui::CalcTextSize("A").y * 2.0f;
    const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x * 5.f;
 
    ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * MAX_LAYER);
    static float inner_width = TEXT_BASE_WIDTH * (MAX_LAYER);
    static ImGuiTableFlags flags2 = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;

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
                //ImGui::TextUnformatted(ToString((LAYER_TYPE)(MAX_LAYER - ImGui::TableGetColumnIndex())));
                ImGui::Text("%d", (MAX_LAYER - ImGui::TableGetColumnIndex()));
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
            //ImGui::Text("%d, %d", ImGui::TableGetRowIndex() - 1, MAX_LAYER - ImGui::TableGetColumnIndex());
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

    return 0;
}

