#pragma once
#include "CComponent.h"

#include "CPhysXMgr.h"

using namespace physx;

class CCollider3D : public CComponent
{
protected:
    SHAPE_TYPE  m_ShapeType;
    ACTOR_TYPE m_eActorType;

    PxShape*            m_pShape;
    PxMaterial*         m_pMaterial;
    PxRigidActor*     m_pRigidActor;

    PXUSERDATA  m_pUserData;

    Vec3            m_vOffsetPos;
    Vec3            m_vOffsetScale;

    Matrix          m_matCollider3D;    
    
    int             m_iCollisionCount;

    bool            m_bAbsolute;
    bool            m_MeshChanged;    // Obj의 Mesh가 변했을 경우 Shape를 다시 업데이트해줘야 함.

public:
    void CreateRigidActor();
    void AddRigidActor();

    void UpdateActorInfo();
    
    void ChangeFilterData();
    void EditCapsuleShape(float _radius, float _halfHeight);
    void EditBoxShape(Vec3 _halfExtents);
    void EditConvexShape(Vec3 _scale);
    void SetGravity(bool _gravity);
    Vec3 GetBoxExtents();
    float GetCapsuleRadius();
    float GetCapsuleHalfHeight();

public:
    virtual void begin() override;
    virtual void finaltick() override;

public:
    void SetOffsetPos(Vec3 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetOffsetScale(Vec3 _vOffsetScale) { m_vOffsetScale = _vOffsetScale; }
    void SetAbsolute(bool _bSet) { m_bAbsolute = _bSet; }
    void SetActorType(ACTOR_TYPE _Type) { m_eActorType = _Type; }
    
public:
    const Matrix& GetColliderWorldMat() { return m_matCollider3D; }
    PxRigidActor* GetRigidActor() { return m_pRigidActor; }
    ACTOR_TYPE GetActorType() { return m_eActorType; }
    SHAPE_TYPE GetShapeType() { return m_ShapeType; }

public:
    void OnCollisionEnter(CCollider3D* _Other);
    void OnCollisionStay(CCollider3D* _Other);
    void OnCollisionExit(CCollider3D* _Other);

    void OnTriggerEnter(CCollider3D* _Other);
    void OnTriggerExit(CCollider3D* _Other);

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CCollider3D);
public:
    CCollider3D();
    ~CCollider3D();
};