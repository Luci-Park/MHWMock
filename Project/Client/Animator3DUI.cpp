#include "pch.h"
#include "Animator3DUI.h"
#include <Engine/CAnimator3D.h>
#include <Engine/CAnimationClip.h>

Animator3DUI::Animator3DUI()
    :ComponentUI("##Animator3D", COMPONENT_TYPE::ANIMATOR3D)
    , m_mapAnimator()
{
    SetName("Animator");
}

Animator3DUI::~Animator3DUI()
{
    for (auto pair : m_mapAnimator)
        delete pair.second;
}
int Animator3DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;
    CAnimator3D* pAnim = GetTarget()->Animator3D();    
    AnimatorGraphEditorWindow* pGraphic;
    
    auto iter = m_mapAnimator.find(pAnim);
    if (iter == m_mapAnimator.end())
    {
        pGraphic = new AnimatorGraphEditorWindow(pAnim);
        m_mapAnimator.insert(make_pair(pAnim, pGraphic));
    }
    else
    {
        pGraphic = iter->second;
    }
    pGraphic->OnDraw();        


    return 0;
}
