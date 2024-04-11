#include "pch.h"
#include "AnjActionPicker.h"
#include <random>

AnjActionPicker::AnjActionPicker(CAnjanath* _parent)
    : m_pParent(_parent)
{
    m_Actions[(int)ANJ_ACTION::ROAR] = new Anj_Roar(_parent);
}

AnjActionPicker::~AnjActionPicker()
{
	Safe_Del_Array(m_Actions);
}

AnjAction* AnjActionPicker::PickAction(ANJ_ACTION _action)
{
	if (_action != ANJ_ACTION::NONE) return m_Actions[(int)_action];

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
    return vecActions[randomIndex];
}
