#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CHeightMapShader.h"
#include "CRaycastShader.h"
#include "CWeightMapShader.h"

enum class LANDSCAPE_MOD
{
    HEIGHT_MAP,
    SPLAT,
    NONE,
};

struct tWeight_4
{
    float arrWeight[4];
};


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
    Ptr<CTexture>           m_HeightMap;        // ���̸� �ؽ���

    Ptr<CWeightMapShader>   m_pCSWeightMap;     // ����ġ ���̴�
    CStructuredBuffer* m_pWeightMapBuffer; // ����ġ ���� ����
    UINT					m_iWeightWidth;		// ����ġ ���� ���μ��� ��� ��
    UINT					m_iWeightHeight;	// ����ġ ���� ���μ��� ��� ��
    UINT                    m_iWeightIdx;		// ���� ��ų ����ġ ����

    LANDSCAPE_MOD           m_eMod; 	        // ���� ����忡�� ���°�

    Ptr<CTexture>           m_pTileArrTex;      // Ÿ�� �迭 �ؽ���
    Ptr<CTexture>           m_pBML;      // Ÿ�� �迭 �ؽ���
    Ptr<CTexture>           m_pNM;      // Ÿ�� �迭 �ؽ���
    
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

