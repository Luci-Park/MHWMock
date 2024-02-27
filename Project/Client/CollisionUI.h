#pragma once
#include "UI.h"

class CCollisionMgr;
class CCollider3D;
class TreeUI;
class TreeNode;

class CollisionUI :
    public UI
{
private:
    bool	m_bCollisionMap[MAX_LAYER][MAX_LAYER];
    char* m_pLabel[(MAX_LAYER + 1) * (MAX_LAYER + 1)];

public:
    virtual void init() override;
    virtual void tick() override;
    virtual int render_update() override;

public:
    CollisionUI();
    ~CollisionUI();
};

