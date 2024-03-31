#pragma once
#include "CComponent.h"

class CTransform :
    public CComponent
{
private:
    Vec3        m_vRelativePos;
    Vec3        m_vRelativeScale;
    Vec3        m_vRelativeRot;

    bool        m_bAbsolute;    // 상대 이동, 크기를 절대값으로 지정    

    Vec3        m_vRelativeDir[3];
    Vec3        m_vWorldDir[3];

    Matrix      m_matWorldScale;    // 월드 크기 행렬
    Matrix      m_matWorld; // 크기, 회전, 이동 정보를 합쳐놓음
    Matrix      m_matWorldInv;

public:
    void SetRelativePos(Vec3 _vPos) { m_vRelativePos = _vPos; BuildWorldMatrix();}
    void SetRelativeScale(Vec3 _vScale) { m_vRelativeScale = _vScale; BuildWorldMatrix();}
    void SetRelativeRot(Vec3 _vRot) { m_vRelativeRot = _vRot; BuildWorldMatrix();}
    void SetRelativeRot(Quaternion _qRot) { m_vRelativeRot = _qRot.ToEuler(); BuildWorldMatrix();}

    void SetRelativePos(float _x, float _y, float _z) { m_vRelativePos = Vec3(_x, _y, _z); BuildWorldMatrix();}
    void SetRelativeScale(float _x, float _y, float _z) { m_vRelativeScale = Vec3(_x, _y, _z); BuildWorldMatrix();}
    void SetRelativeRot(float _x, float _y, float _z) { SetRelativeRot(Vec3(_x, _y, _z));  BuildWorldMatrix();}

    // 상대 이동, 크기를 절대값으로 지정  
    void SetAbsolute(bool _Set) { m_bAbsolute = _Set; }    

    Vec3 GetRelativePos() const { return m_vRelativePos; }
    Vec3 GetRelativeScale() const { return m_vRelativeScale; }
    Quaternion GetRelativeRot() const { return Quaternion::FromEuler(m_vRelativeRot); }
    Vec3 GetRelativeEulerRot() const { return m_vRelativeRot; }

    Vec3 GetRelativeDir(DIR_TYPE _type) const { return m_vRelativeDir[(UINT)_type]; }
    Vec3 GetWorldDir(DIR_TYPE _type) const { { return m_vWorldDir[(UINT)_type]; } }
    Vec3 GetWorldPos() { return m_matWorld.Translation(); }
    Quaternion GetWorldRot();
    Vec3 GetWorldEulerRot();
    Vec3 GetWorldScale();

    bool Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) { return m_matWorld.Decompose(scale, rotation, translation); }
    bool Decompose(Vector3& scale, Vector3& rotation, Vector3& translation) { 
        Quaternion qRot;
        bool rslt = m_matWorld.Decompose(scale, qRot, translation);
        rotation = qRot.ToEuler();
        return rslt;
    }


    const Matrix& GetWorldScaleMat() { return m_matWorldScale; }
    const Matrix& GetWorldMat() const { return m_matWorld; }
    const Matrix& GetWorldInvMat() const { return m_matWorldInv; }

    void SetWorldMat(const Matrix& _mat) { m_matWorld = _mat; }

    void UpdateSimulateResult(Vector3 _Pos, Quaternion _Rot);

public:
    virtual void finaltick() override;    
    void UpdateData();

    void operator = (const CTransform& _OtherTransform)
    {
		m_vRelativePos = _OtherTransform.m_vRelativePos;
		m_vRelativeScale = _OtherTransform.m_vRelativeScale;
		m_vRelativeRot = _OtherTransform.m_vRelativeRot;
		m_bAbsolute = _OtherTransform.m_bAbsolute;
		m_matWorldScale = _OtherTransform.m_matWorldScale;
		m_matWorld = _OtherTransform.m_matWorld;
		m_matWorldInv = _OtherTransform.m_matWorldInv;


        for (int i = 0; i < 3; ++i)
        {
            m_vRelativeDir[i] = _OtherTransform.m_vRelativeDir[i];
            m_vWorldDir[i] = _OtherTransform.m_vWorldDir[i];
        }
    }

private:
    void BuildWorldMatrix();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CTransform);
public:
    CTransform();
    ~CTransform();
};

