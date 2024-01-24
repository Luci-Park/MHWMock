#include "pch.h"
#include "Light3DUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CLight3d.h>

Light3DUI::Light3DUI()
    : ComponentUI("##Light3D", COMPONENT_TYPE::LIGHT3D)
{
    SetName("Light3D");
}

Light3DUI::~Light3DUI()
{
}


int Light3DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;


    LIGHT_TYPE vLType = GetTarget()->Light3D()->GetLightType();
    static UINT vLTypeint = (UINT)vLType;
    Vec3 vLightColor = GetTarget()->Light3D()->GetLightColor();
    Vec3 vLightAmb = GetTarget()->Light3D()->GetLightAmbient();
    float vLRadius = 0.0;
    float vLAngle = 0.0;
    if (vLType == LIGHT_TYPE::POINT)
        vLRadius = GetTarget()->Light3D()->GetRadius();
    else if (vLType == LIGHT_TYPE::SPOT)
        vLAngle == GetTarget()->Light3D()->GetAngle();

    ImGui::Text("Light Type ");
    ImGui::SameLine();
    const char* items[] = { "DirectionalLight##", "PointLight##", "SpotLight##" };
    const char* combo_preview_value = items[vLTypeint];  // Pass in the preview value visible before opening the combo (it could be anything)
    if (ImGui::BeginCombo("##", combo_preview_value, ImGuiComboFlags_NoArrowButton))
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            const bool is_selected = (vLTypeint == n);
            if (ImGui::Selectable(items[n], is_selected))
                vLTypeint = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::Text("Light Color");
    ImGui::SameLine();
    ImGui::ColorEdit3("##lcolor", vLightColor);

    ImGui::Text("Light Amb  "); 
    ImGui::SameLine();
    ImGui::ColorEdit3("##lamb", vLightAmb);

    if (vLType == LIGHT_TYPE::POINT)
    {
        ImGui::Text("Radius     ");
        ImGui::SameLine();
        ImGui::DragFloat("##lradius", &vLRadius);
    }
    else if (vLType == LIGHT_TYPE::SPOT)
    {
        ImGui::Text("Radius     ");
        ImGui::SameLine();
        ImGui::DragFloat("##langle", &vLAngle);
    }

    GetTarget()->Light3D()->SetLightType((LIGHT_TYPE)vLTypeint);
    GetTarget()->Light3D()->SetLightColor(vLightColor);
    GetTarget()->Light3D()->SetLightAmbient(vLightAmb);
    GetTarget()->Light3D()->SetRadius(vLRadius);
    vLAngle = (vLAngle / 180.0f) * XM_PI;
    GetTarget()->Light3D()->SetAngle(vLAngle);

    return TRUE;
}