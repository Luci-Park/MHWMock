#include "pch.h"
#include "CLandScape.h"

#include "CRenderMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CStructuredBuffer.h"

#include "CTransform.h"
#include "CCamera.h"

CLandScape::CLandScape()
	: CRenderComponent(COMPONENT_TYPE::LANDSCAPE)
	, m_iFaceX(1)
	, m_iFaceZ(1)
	, m_vBrushScale(Vec2(0.05f, 0.05f))
{
	init();
}

CLandScape::~CLandScape()
{
	if (nullptr != m_pCrossBuffer)
		delete m_pCrossBuffer;
}


void CLandScape::finaltick()
{
	if (KEY_PRESSED(KEY::LBTN))
	{
		Raycasting();

		// ���� ��ġ������ ���� ���̸� ���� ��
		m_pCSHeightMap->SetInputBuffer(m_pCrossBuffer); // ��ŷ ������ HeightMapShader �� ����

		m_pCSHeightMap->SetBrushTex(m_pBrushTex);		// ����� �귯�� �ؽ��� ����
		m_pCSHeightMap->SetBrushIndex(0);				// �귯�� �ε��� ����
		m_pCSHeightMap->SetBrushScale(m_vBrushScale);   // �귯�� ũ��
		m_pCSHeightMap->SetHeightMap(m_HeightMap);
		m_pCSHeightMap->Execute();
	}
}

void CLandScape::render()
{
	if (GetMesh() == nullptr || GetMaterial() == nullptr)
		return;

	Transform()->UpdateData();

	//GetMaterial()->GetShader()->SetRSType(RS_TYPE::WIRE_FRAME);

	GetMaterial()->SetScalarParam(INT_0, &m_iFaceX);
	GetMaterial()->SetScalarParam(INT_1, &m_iFaceZ);
	GetMaterial()->SetTexParam(TEX_2, m_HeightMap);

	GetMaterial()->UpdateData();

	GetMesh()->render();
}


void CLandScape::SetFace(UINT _iFaceX, UINT _iFaceZ)
{
	m_iFaceX = _iFaceX;
	m_iFaceZ = _iFaceZ;

	CreateMesh();
}


void CLandScape::Raycasting()
{
	// ���� ī�޶� ������
	CCamera* pMainCam = CRenderMgr::GetInst()->GetMainCam();
	if (nullptr == pMainCam)
		return;

	// ���� ���� ������ ������ ���÷� ����
	const Matrix& matWorldInv = Transform()->GetWorldInvMat();
	const tRay& ray = pMainCam->GetRay();

	tRay CamRay = {};
	CamRay.vStart = XMVector3TransformCoord(ray.vStart, matWorldInv);
	CamRay.vDir = XMVector3TransformNormal(ray.vDir, matWorldInv);
	CamRay.vDir.Normalize();

	// ������ ī�޶� Ray �� ������ ����
	tRaycastOut out = { Vec2(0.f, 0.f), 0x7fffffff, 0 };
	m_pCrossBuffer->SetData(&out, 1);

	m_pCSRaycast->SetHeightMap(m_HeightMap);
	m_pCSRaycast->SetFaceCount(m_iFaceX, m_iFaceZ);
	m_pCSRaycast->SetCameraRay(CamRay);
	m_pCSRaycast->SetOuputBuffer(m_pCrossBuffer);

	m_pCSRaycast->Execute();

	m_pCrossBuffer->GetData(&out);
	int a = 0;
}