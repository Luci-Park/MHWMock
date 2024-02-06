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
    return 0;
}

