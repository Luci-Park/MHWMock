#include "pch.h"
#include "LandScapeUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CLandScape.h>

LandScapeUI::LandScapeUI()
    : ComponentUI("##LandScape", COMPONENT_TYPE::LANDSCAPE)
{
    SetName("LandScape");
}

LandScapeUI::~LandScapeUI()
{
}

int LandScapeUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    int viFaceX = GetTarget()->LandScape()->GetFaceX();
    int viFaceZ = GetTarget()->LandScape()->GetFaceZ();

    Ptr<CTexture> vHeightMap = GetTarget()->LandScape()->GetHeightMap();

    ImGui::Text("iFaceX");
    ImGui::SameLine();
    ImGui::DragInt("There is a risk of frame-drop##iFaceX", &viFaceX);
    ImGui::Text("iFaceZ");
    ImGui::SameLine();
    ImGui::DragInt("##iFaceZ", &viFaceZ);

    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

    ImGui::Image(vHeightMap->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);

    GetTarget()->LandScape()->SetFace(viFaceX, viFaceZ);
    //GetTarget()->LandScape()->SetHeightMap(vHeightMap);


	return TRUE;
}
