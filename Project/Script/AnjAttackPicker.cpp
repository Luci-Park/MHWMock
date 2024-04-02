#include "pch.h"
#include "AnjAttackPicker.h"

AnjAttackPicker::AnjAttackPicker(CAnjanath* _parent)
    :m_pParent(_parent)
{
    m_pAttacks[(UINT)ANJ_ATTACK::WEAK_BITE] = new WeakBite(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::BITE] = new Bite(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::CONTIN_BITE] = new ContinBite(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::CLAW] = new Claw(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::TAIL_SLAM] = new TailSlam(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::TAIL_SWEEP] = new TailSweep(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::BODY_SLAM] = new BodySlam(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::FORWARD] = new ForwardAtk(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::RUSH] = new Rush(_parent);
    m_pAttacks[(UINT)ANJ_ATTACK::FLAME] = new Flame(_parent);
}

AnjAttackPicker::~AnjAttackPicker()
{
    for (int i = 0; i < (UINT)ANJ_ATTACK::NONE; i++)
    {
        delete m_pAttacks[i];
        m_pAttacks[i] = nullptr;
    }
}

AnjAttack* AnjAttackPicker::PickAttack()
{
    return nullptr;
}