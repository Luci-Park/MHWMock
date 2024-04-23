#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CHeightMapShader.h"
#include "CRaycastShader.h"

class CLandScape :
    public CRenderComponent
{
private:
    UINT                    m_iFaceX;
    UINT                    m_iFaceZ;

    Vec2                    m_vBrushScale;      // �귯�� ũ��(��ü ������� ũ�� ������)
    Ptr<CTexture>           m_pBrushTex;        // �귯���� �ؽ���

    Ptr<CRaycastShader>     m_pCSRaycast;       // ��ŷ ���̴�
    CStructuredBuffer* m_pCrossBuffer;	    // ���콺 ��ŷ�Ǵ� ���� ���� �޴� ����

    Ptr<CHeightMapShader>   m_pCSHeightMap;     // ���̸� ���̴�
    Ptr<CTexture>           m_HeightMap;       // ���̸� �ؽ���

public:
    void SetFace(UINT _iFaceX, UINT _iFaceZ);
    void SetHeightMap(Ptr<CTexture> _HeightMap) { m_HeightMap = _HeightMap; }

    virtual void finaltick() override;
    virtual void render() override;


private:
    void init();
    void CreateMesh();
    void CreateComputeShader();
    void CreateTexture();

    void Raycasting();

    CLONE(CLandScape);
public:
    CLandScape();
    ~CLandScape();
};

