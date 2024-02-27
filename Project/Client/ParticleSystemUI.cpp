#include "pch.h"
#include "ParticleSystemUI.h"
#include "ListUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CParticleSystem.h>
#include <Engine\CResMgr.h>

ParticleSystemUI::ParticleSystemUI()
    : ComponentUI("##Particle", COMPONENT_TYPE::PARTICLESYSTEM)
{
    SetName("Particle");
}

ParticleSystemUI::~ParticleSystemUI()
{
}

int ParticleSystemUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;
    tParticleModule pModule = GetTarget()->ParticleSystem()->GetModuleData();
    Ptr<CTexture> pTexture = GetTarget()->ParticleSystem()->GetParticleTexture();
    if (ImGui::CollapsingHeader("Spawn Module"))
    {
        ImGui::Text("Color          ");
        ImGui::SameLine();
        ImGui::DragFloat4("##Color", pModule.vSpawnColor, 0.1f, 0.0f, 1.0f);
        ImGui::Text("ScaleMin       ");
        ImGui::SameLine();
        ImGui::DragFloat4("##Min", pModule.vSpawnScaleMin);
        ImGui::Text("ScaleMax       ");
        ImGui::SameLine();
        ImGui::DragFloat4("##Max", pModule.vSpawnScaleMax);
        ImGui::Text("SpawnRate      ");
        ImGui::SameLine();
        ImGui::DragInt("##Rate", &pModule.SpawnRate);
        ImGui::Text("Life: min / max");
        ImGui::SameLine();
        ImGui::DragFloat2("##Life", &(pModule.MinLifeTime, pModule.MaxLifeTime));
        ImGui::Text("Space          ");
        ImGui::SameLine();
        const char* SpaceItems[2] = { "Local##", "World##" };
        const char* Space_combo_preview_value = SpaceItems[0];  // Pass in the preview value visible before opening the combo (it could be anything)
        if (ImGui::BeginCombo("##", Space_combo_preview_value, ImGuiComboFlags_NoArrowButton))
        {
            for (int n = 0; n < IM_ARRAYSIZE(SpaceItems); n++)
            {
                const bool is_selected = (pModule.SpawnShapeType == n);
                if (ImGui::Selectable(SpaceItems[n], is_selected))
                    pModule.SpawnShapeType = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::Text("ShapeType      ");
        ImGui::SameLine();
        const char* ShapeTypeItems[2] = { "Box##", "Sphere##" };
        const char* ShapeType_combo_preview_value = ShapeTypeItems[0];  // Pass in the preview value visible before opening the combo (it could be anything)
        if (ImGui::BeginCombo("##", ShapeType_combo_preview_value, ImGuiComboFlags_NoArrowButton))
        {
            for (int n = 0; n < IM_ARRAYSIZE(ShapeTypeItems); n++)
            {
                const bool is_selected = (pModule.SpawnShapeType == n);
                if (ImGui::Selectable(ShapeTypeItems[n], is_selected))
                    pModule.SpawnShapeType = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        if (pModule.SpawnShapeType == 0)
        {
            ImGui::Text("BoxScale       ");
            ImGui::SameLine();
            ImGui::DragFloat3("##BoxScale", pModule.vBoxShapeScale);
        }
        else
        {
            ImGui::Text("SphereRadius   ");
            ImGui::SameLine();
            ImGui::DragFloat("##SphereRadius", &pModule.fSphereShapeRadius);
        }
    }
    if (ImGui::CollapsingHeader("Color Change Module"))
    {
        ImGui::Text("StartColor     ");
        ImGui::SameLine();
        ImGui::DragFloat4("##StartColor", pModule.vStartColor, 0.1f, 0.0f, 1.0f);
        ImGui::Text("EndColor       ");
        ImGui::SameLine();
        ImGui::DragFloat4("##EndColor", pModule.vEndColor, 0.1f, 0.0f, 1.0f);
    }
    if (ImGui::CollapsingHeader("Scale Change Module"))
    {
        ImGui::Text("StartScale     ");
        ImGui::SameLine();
        ImGui::DragFloat("##StartScale", &pModule.StartScale);
        ImGui::Text("EndScale       ");
        ImGui::SameLine();
        ImGui::DragFloat("##EndScale", &pModule.EndScale);
    }
    if (ImGui::CollapsingHeader("Add Velocity Module"))
    {
        ImGui::Text("VelocityType   ");
        ImGui::SameLine();
        ImGui::DragInt("##VelocityType", &pModule.AddVelocityType, 0.1f, 0, 2);
        ImGui::Text("VelocityDir    ");
        ImGui::SameLine();
        ImGui::DragFloat4("##VelocityDir", pModule.vVelocityDir, 0.05f, -1.f, 1.f);
        ImGui::Text("OffsetAngle    ");
        ImGui::SameLine();
        ImGui::DragFloat("##OffsetAngle", &pModule.OffsetAngle);
        ImGui::Text("Speed          ");
        ImGui::SameLine();
        ImGui::DragFloat("##Speed", &pModule.Speed);       
    }
    if (ImGui::CollapsingHeader("Drag Module"))
    {
        ImGui::Text("StartDrag      ");
        ImGui::SameLine();
        ImGui::DragFloat("##StartDrag", &pModule.StartDrag);
        ImGui::Text("EndDrag        ");
        ImGui::SameLine();
        ImGui::DragFloat("##EndDrag", &pModule.EndDrag);
    }
    if (ImGui::CollapsingHeader("Noise Force Module"))
    {
        ImGui::Text("NoiseTerm      ");
        ImGui::SameLine();
        ImGui::DragFloat("##NoiseTerm", &pModule.fNoiseTerm);
        ImGui::Text("NoiseForce     ");
        ImGui::SameLine();
        ImGui::DragFloat("##NoiseForce", &pModule.fNoiseForce);
    }
    if (ImGui::CollapsingHeader("Render Module"))
    {
        ImGui::Text("VelocityAlign  ");
        ImGui::SameLine();
        ImGui::DragInt("##VelocityAlign", &pModule.VelocityAlignment, 1.f, 0, 1);
        ImGui::Text("VelocityScale  ");
        ImGui::SameLine();
        ImGui::DragInt("##VelocityScale", &pModule.VelocityScale, 1.f, 0, 1);
        ImGui::Text("MaxSpeed       ");
        ImGui::SameLine();
        ImGui::DragFloat("##MaxSpeed", &pModule.vMaxSpeed);
        ImGui::Text("MaxVelScale    ");
        ImGui::SameLine();
        ImGui::DragFloat4("##MaxVelScale", pModule.vMaxVelocityScale);
    }
    if (ImGui::CollapsingHeader("ParticleTexture"))
    {
        ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
        ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
        ImGui::Text("ParticleTexture");
        ImGui::Image((ImTextureID)pTexture->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);

        if (ImGui::Button("##TextureSelect", ImVec2(18, 18)))
        {
            const map<wstring, Ptr<CRes>>& pTex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

            ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
            pListUI->Reset("Texture", ImVec2(300.f, 500.f));
            for (const auto& pair : pTex)
            {
                pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
            }

            // 항목 선택시 호출받을 델리게이트 등록
            pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&ParticleSystemUI::SelectTexture);
        }

    }

    GetTarget()->ParticleSystem()->SetModuleData(pModule);


    ComponentUI::RemoveComponent();

    return TRUE;
}

void ParticleSystemUI::SelectTexture(DWORD_PTR _Key)
{
    string strKey = (char*)_Key;
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));
    GetTarget()->ParticleSystem()->SetParticleTexture(pTex);
}
