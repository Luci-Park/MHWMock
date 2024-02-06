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

    // ���� ���������� 8���� ��
    Vec3        m_arrProj[8];


    // ����ü�� 6��
    Vec4        m_arrFace[FT_END];

public:

    void finaltick();
    // ���� ������ ����
    CFrustum& operator=(const CFrustum& other) {
        if (this == &other) // �ڱ� �ڽſ� ���� ������ ��� ó��
            return *this;

        this->m_pCam = other.m_pCam;
        memcpy(this->m_arrFace, other.m_arrFace, sizeof(Vec4) * FT_END);
        memcpy(this->m_arrProj, other.m_arrProj, sizeof(Vec3) * 8);
        return *this; // ���� �����ڴ� *this�� ��ȯ�Ͽ� ���� ���� �����ϰ� ��
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

