#include "pch.h"
#include "Animator3DUI.h"
#include <Engine/CAnimator3D.h>
#include <Engine/CAnimationClip.h>

Animator3DUI::Animator3DUI()
    :ComponentUI("##Animator3D", COMPONENT_TYPE::ANIMATOR3D)
{
    SetName("Animator");
}

Animator3DUI::~Animator3DUI()
{
}
int Animator3DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;
    Gizmo();
    return 0;
}

void Animator3DUI::Gizmo()
{
    static FitOnScreen fit = Fit_None;
    ImGui::Begin("Animator", NULL, 0);
    if (ImGui::Button("Fit all nodes"))
    {
        fit = Fit_AllNodes;
    }
    ImGui::SameLine();
    if (ImGui::Button("Fit selected nodes"))
    {
        fit = Fit_SelectedNodes;
    }
    ImGui::End();    
}
