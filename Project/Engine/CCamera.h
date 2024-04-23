#pragma once
#include "CComponent.h"

#include "CFrustum.h"

class CCamera :
    public CComponent
{
private:
    CFrustum    m_Frustum;

    float       m_fAspectRatio;
    float       m_fScale;           // Orthograpic 에서 사용하는 카메라 배율
    float       m_fFar;
    float       m_fNear;
    float       m_fFOV;

    float       m_fOrthoWidth;       // Orthgraphic 에서의 가로 투영 범위
    float       m_fOrthoHeight;      // OrthGraphic 에서의 세로 투영 범위

    PROJ_TYPE   m_ProjType;

    Matrix      m_matWorld;
    Matrix      m_matWorldInv;

    Matrix      m_matView;
    Matrix      m_matViewInv;

    Matrix      m_matProj;
    Matrix      m_matProjInv;

    UINT        m_iLayerMask;
    bool        m_iLayerMaskVis[MAX_LAYER];

    int         m_iCamIdx;          // 카메라 우선순위
    tRay                    m_ray;      // 마우스 방향을 향하는 직선

    vector<CGameObject*>    m_vecDeferred;
    vector<CGameObject*>    m_vecDeferredDecal;

    vector<CGameObject*>    m_vecOpaque;
    vector<CGameObject*>    m_vecMask;
    vector<CGameObject*>    m_vecDecal;
    vector<CGameObject*>    m_vecTransparent;
    vector<CGameObject*>    m_vecUI;
    vector<CGameObject*>    m_vecPost;

    vector<CGameObject*>    m_vecShadow;



public:
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
    PROJ_TYPE GetProjType() { return m_ProjType; }

    void SetScale(float _fScale) { m_fScale = _fScale; }
    float GetScale() { return m_fScale; }

    void SetFar(float _Far) { m_fFar = _Far; }
    float GetFar() { return m_fFar; }

    void SetNear(float _Near) { m_fNear = _Near; }
    float GetNear() { return m_fNear; }

    void SetLayerMask(int _iLayer, bool _Visible);
    void SetLayerMaskAll(bool _Visible);
    UINT GetLayerMask() { return m_iLayerMask; }
    bool GetLayerMaskVisible(int _iLayer) { return m_iLayerMaskVis[_iLayer]; }

    void SetFOV(float _Radian) { m_fFOV = _Radian; }
    float GetFOV() { return m_fFOV; }

    void SetAspectRatio(float _Ratio) { m_fAspectRatio = _Ratio; }
    float GetAspectRatio() { return m_fAspectRatio; }

    void SetOrthoWidth(float _width) { m_fOrthoWidth = _width; }
    void SetOrthoHeight(float _height) { m_fOrthoHeight = _height; }

    float GetorthoWidth() { return m_fOrthoWidth; }
    float GetOrthoHeight() { return m_fOrthoHeight; }

    void SetCameraIndex(int _idx);

    const tRay& GetRay() { return m_ray; }

    const Matrix& GetViewMat() { return m_matView; }
    const Matrix& GetProjMat() { return m_matProj; }

    const Matrix& GetViewInvMat() { return m_matViewInv; }
    const Matrix& GetProjInvMat() { return m_matProjInv; }

public:
    void SortObject();
    void SortObject_Shadow();
    void render();
    void render_shadowmap();
    void render_ui();

public:
    virtual void begin() override;
    virtual void finaltick() override;

protected:
    void CalRay();  // 마우스 방향으로 광선 연산

private:
    void clear();
    void clear_shadow();

    void render_deferred();
    void render_opaque();
    void render_mask();
    void render_decal();
    void render_transparent();
    void render_postprocess();

    void CalcViewMat();
    void CalcProjMat();


    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CCamera);
public:
    CCamera();
    CCamera(const CCamera& _Other);
    ~CCamera();
};

