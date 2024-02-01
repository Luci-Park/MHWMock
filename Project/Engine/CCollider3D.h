#pragma once
#include "CComponent.h"

class CCollider3D : public CComponent
{
private:
    Vec3            m_vOffsetPos;
    Vec3            m_vOffsetScale;

    Matrix          m_matCollider3D;    
    
    int               m_iCollisionCount;

    bool             m_bAbsolute;
    bool             m_MeshChanged;    // Obj�� Mesh�� ������ ��� Shape�� �ٽ� ������Ʈ����� ��.
    
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