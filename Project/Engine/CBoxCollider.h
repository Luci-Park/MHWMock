#pragma once
#include "CCollider3D.h"
class CBoxCollider :
    public CCollider3D
{
private:
    Vec3 _HalfExtents;
public:
    void CreateColliderShape();

public:
    void SetExtents(Vec3 halfextens) { _HalfExtents = halfextens; }

public:
    Vec3 GetExtents() { return _HalfExtents; }

public:
    virtual void begin() override;
    virtual void finaltick() override;

public:
    CBoxCollider();
    ~CBoxCollider();
};

