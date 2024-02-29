#pragma once
#include "CCollider3D.h"

class CConvexCollider : public CCollider3D
{
private:
    PxTriangleMesh* m_pTriangleMesh;
    Vec3 _ConvexScale;

public:
    void CookingTriangleMesh(void* _pPoints, UINT _VtxCount, void* _pIndices, UINT _IdxCount);
    void CreateColliderShape();

public:
    virtual void begin() override;
    virtual void finaltick() override;

public:
    CConvexCollider();
    ~CConvexCollider();
};

