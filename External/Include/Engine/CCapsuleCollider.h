#pragma once
#include "CCollider3D.h"

class CCapsuleCollider : public CCollider3D
{
private:
    

public:
    void CreateColliderShape();

public:
    virtual void begin() override;
    virtual void finaltick() override;

public:
    CCapsuleCollider();
    ~CCapsuleCollider();
};

