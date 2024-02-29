#pragma once
#include "CCollider3D.h"

class CCapsuleCollider : public CCollider3D
{
private:
    float _CapsuleRadius;
    float _CapsuleHeight;
public:
    void CreateColliderShape();
public:
    void SetRadius(float radius) { _CapsuleRadius = radius; }
    void SetHalfHeight(float halfHeight) { _CapsuleHeight = halfHeight; }
public:
    float GetRadius() { return _CapsuleRadius; }
    float GetHeight() { return _CapsuleHeight; }
public:
    virtual void begin() override;
    virtual void finaltick() override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

public:
    CCapsuleCollider();
    ~CCapsuleCollider();
};

