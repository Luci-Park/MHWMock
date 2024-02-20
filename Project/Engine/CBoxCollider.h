#pragma once
#include "CCollider3D.h"
class CBoxCollider :
    public CCollider3D
{
private:


public:
    void CreateColliderShape();

public:
    virtual void begin() override;
    virtual void finaltick() override;

public:
    CBoxCollider();
    ~CBoxCollider();
};

