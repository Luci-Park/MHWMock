#include "pch.h"
#include "AnjActionPicker.h"
#include <random>

AnjActionPicker::AnjActionPicker(CAnjanath* _parent)
    : m_pParent(_parent)
    , m_prevAction(ANJ_ACTION::NONE)
{
    m_Actions[(int)ANJ_ACTION::ROAR] = new Anj_Roar(_parent);
    m_Actions[(int)ANJ_ACTION::BITE] = new Anj_Bite(_parent);
    m_Actions[(int)ANJ_ACTION::CONTIN_BITE] = new Anj_ContinBite(_parent);
    m_Actions[(int)ANJ_ACTION::CLAW_SCRATCH] = new Anj_ClawScratch(_parent);
    m_Actions[(int)ANJ_ACTION::TAIL_SLAM] = new Anj_TailSlam(_parent);
    m_Actions[(int)ANJ_ACTION::TAIL_SWEEP] = new Anj_TailSweep(_parent);
    m_Actions[(int)ANJ_ACTION::BODY_SLAM] = new Anj_BodySlam(_parent);
    m_Actions[(int)ANJ_ACTION::FORWARD_ATK] = new Anj_ForwardAtk(_parent);
    m_Actions[(int)ANJ_ACTION::RUSH] = new Anj_Rush(_parent);
}

AnjActionPicker::~AnjActionPicker()
{
	Safe_Del_Array(m_Actions);
}

AnjAction* AnjActionPicker::PickAction(ANJ_ACTION _action)
{
    if (_action != ANJ_ACTION::NONE)
    {
        m_prevAction = _action;
        return m_Actions[(int)_action];
    }

    vector<AnjAction*>vecActions;
    for (int i = 0; i < (UINT)ANJ_ACTION::NONE; i++)
    {
        if (m_Actions[i]->Pickable()) vecActions.push_back(m_Actions[i]);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, vecActions.size() - 1);

    // Generate a random index
    int randomIndex = dis(gen);
    while (vecActions.size() > 1 && vecActions[randomIndex]->GetType() == m_prevAction)
        randomIndex = dis(gen);

    m_prevAction = vecActions[randomIndex]->GetType();
    return vecActions[randomIndex];
}
