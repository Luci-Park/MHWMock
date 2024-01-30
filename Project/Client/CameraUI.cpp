#include "pch.h"
#include "CameraUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CCamera.h>
#include <Engine\CTransform.h>
#include <Engine\CFrustum.h>

CameraUI::CameraUI()
    : ComponentUI("##Camera", COMPONENT_TYPE::CAMERA)
{
    SetName("Camera");
}

CameraUI::~CameraUI()
{
}

int CameraUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    float vFar = GetTarget()->Camera()->GetFar();
    float vNear = GetTarget()->Camera()->GetNear();
    float vFOV = GetTarget()->Camera()->GetFOV();
    float vRatio = GetTarget()->Camera()->GetAspectRatio();

    ImGui::Text("Far    ");
    ImGui::SameLine();
    ImGui::DragFloat("##Far", &vFar);
    ImGui::Text("Near   ");
    ImGui::SameLine();
    ImGui::DragFloat("##Near", &vNear);
    ImGui::Text("FOV    ");
    ImGui::SameLine();
    ImGui::DragFloat("##FOV", &vFOV);
    ImGui::Text("ARatio ");
    ImGui::SameLine();
    ImGui::DragFloat("##ARatio", &vRatio);
    char* items[MAX_LAYER];
    bool check[MAX_LAYER];
    if (ImGui::CollapsingHeader("Layer Mask"))
    {
        for (size_t i = 0; i < MAX_LAYER; i++)
        {
            if (LAYER_TYPE_STR[i] != "")
            {
                check[i] = GetTarget()->Camera()->GetLayerMaskVisible(i);
                items[i] = new char[strlen(LAYER_TYPE_STR[i])];
                strcpy(const_cast<char*>(items[i]), LAYER_TYPE_STR[i]);
                ImGui::Checkbox(items[i], &check[i]);
            }
        }
    }
    for (size_t i = 0; i < MAX_LAYER; i++)
    {
        GetTarget()->Camera()->SetLayerMask(i, check[i]);
    }

    GetTarget()->Camera()->SetFar(vFar);
    GetTarget()->Camera()->SetNear(vNear);
    GetTarget()->Camera()->SetFOV(vFOV);
    GetTarget()->Camera()->SetAspectRatio(vRatio);


    return TRUE;
}
