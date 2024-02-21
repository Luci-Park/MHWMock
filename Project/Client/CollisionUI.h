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

public:
    virtual void init() override;
    virtual void tick() override;
    virtual int render_update() override;

public:
    CollisionUI();
    ~CollisionUI();
};

