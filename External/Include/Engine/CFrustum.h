#pragma once
#include "CEntity.h"

enum FACE_TYPE
{
    FT_NEAR,
    FT_FAR,
    FT_UP,
    FT_DOWN,
    FT_LEFT,
    FT_RIGHT,

    FT_END,
};


class CCamera;

class CFrustum :
    public CEntity
{
private:
    CCamera*    m_pCam;

    // 투영 공간에서의 8개의 점
    Vec3        m_arrProj[8];


    // 절두체의 6면
    Vec4        m_arrFace[FT_END];

public:

    void finaltick();
    // 대입 연산자 정의
    CFrustum& operator=(const CFrustum& other) {
        if (this == &other) // 자기 자신에 대한 대입인 경우 처리
            return *this;

        this->m_pCam = other.m_pCam;
        memcpy(this->m_arrFace, other.m_arrFace, sizeof(Vec4) * FT_END);
        memcpy(this->m_arrProj, other.m_arrProj, sizeof(Vec3) * 8);
        return *this; // 대입 연산자는 *this를 반환하여 연쇄 대입 가능하게 함
    }
public:
    bool FrustumCheck(Vec3 _vPos);
    bool FrustumCheckBound(Vec3 _vPos, float _fRadis);

public:   
    CLONE(CFrustum);



public:
    CFrustum() {}
    CFrustum(CCamera* _Camera);
    ~CFrustum();
};

