#pragma once
#include "CComponent.h"

#include <PxPhysicsApi.h>

// PhysX Library
#ifdef _DEBUG
#pragma comment(lib, "PhysX//PhysX_64")
#pragma comment(lib, "PhysX//PhysXFoundation_64")
#pragma comment(lib, "PhysX//PhysXExtensions_static_64")
#pragma comment(lib, "PhysX//PhysXPvdSDK_static_64")
#else
#pragma comment(lib, "Script//PhysX_64")
#pragma comment(lib, "Script//PhysXFoundation_64")
#pragma comment(lib, "Script//PhysXExtensions_static_64")
#pragma comment(lib, "PhysX//PhysXPvdSDK_static_64")
#endif

using namespace physx;

class CCollider3D : public CComponent
{
private:
    PxShape*        m_pShape;
    PxMaterial*     m_pMaterial;
    PxRigidActor*  m_pRigidActor;
    void*           m_pUserData;

    Vec3            m_vOffsetPos;
    Vec3            m_vOffsetScale;

    Matrix          m_matCollider3D;    
    
    int               m_iCollisionCount;

    bool             m_bAbsolute;
    bool             m_MeshChanged;    // Obj의 Mesh가 변했을 경우 Shape를 다시 업데이트해줘야 함.
    
public:
    virtual void begin() override;
    virtual void finaltick() override;

public:
    void SetOffsetPos(Vec3 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetOffsetScale(Vec3 _vOffsetScale) { m_vOffsetScale = _vOffsetScale; }
    void SetAbsolute(bool _bSet) { m_bAbsolute = _bSet; }

    const Matrix& GetColliderWorldMat() { return m_matCollider3D; }

public:
    void BeginOverlap(CCollider2D* _Other);
    void OnOverlap(CCollider2D* _Other);
    void EndOverlap(CCollider2D* _Other);

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CCollider3D);
public:
    CCollider3D();
    ~CCollider3D();
};