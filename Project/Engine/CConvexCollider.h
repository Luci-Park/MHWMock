#pragma once
#include "CCollider3D.h"

class CConvexCollider : public CCollider3D
{
private:
    PxTriangleMesh* m_pTriangleMesh;

public:
    void CookingTriangleMesh(Vector3* _pPoints, UINT _nNumPoint, UINT* _pIndices, UINT _nNumFace);
    void CreateColliderShape();

public:
    virtual void begin() override;
    virtual void finaltick() override;

public:
    CConvexCollider();
    ~CConvexCollider();
};

