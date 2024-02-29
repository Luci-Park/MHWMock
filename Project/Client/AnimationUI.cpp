#include "pch.h"
#include "AnimationUI.h"
#include <Engine/CAnimationClip.h>

AnimationUI::AnimationUI()
    :ResUI(RES_TYPE::ANIMATION)
{
}

AnimationUI::~AnimationUI()
{
}
int AnimationUI::render_update()
{
    if (!ResUI::render_update())
        return 0;
    return 1;
}
