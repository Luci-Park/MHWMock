#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_vRelativeScale(Vec3(1.f, 1.f, 1.f))
	, m_bAbsolute(false)	
	, m_vRelativeDir{
		  Vec3(1.f, 0.f, 0.f)
		, Vec3(0.f, 1.f, 0.f)
		, Vec3(0.f, 0.f, 1.f)}	
{
	SetName(L"Transform");
}

CTransform::~CTransform()
{
}


void CTransform::finaltick()
{
	BuildWorldMatrix();
}

void CTransform::UpdateData()
{
	// 위치값을 상수버퍼에 전달 및 바인딩		
	CConstBuffer* pTransformBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	g_transform.matWorld = m_matWorld;
	g_transform.matWorldInv = m_matWorldInv;
	g_transform.matWV = g_transform.matWorld * g_transform.matView;
	g_transform.matWVP = g_transform.matWV * g_transform.matProj;


	pTransformBuffer->SetData(&g_transform);
	pTransformBuffer->UpdateData();
}

Quaternion CTransform::GetWorldRot()
{
	Vector3 pos, scale; Quaternion rot;
	Decompose(scale, rot, pos);
	return rot;
}

Vec3 CTransform::GetWorldEulerRot()
{
	return GetWorldRot().ToEuler();
}

Vec3 CTransform::GetWorldScale()
{
	Vector3 pos, scale; Quaternion rot;
	Decompose(scale, rot, pos);
	return scale;
}

void CTransform::UpdateSimulateResult(Vector3 _Pos, Quaternion _Rot)
{
	CGameObject* pParent = GetOwner()->GetParent();

	if (pParent)
	{
		Matrix mParentWorldInv = pParent->Transform()->m_matWorldInv;
		Matrix mWorldMatrix = m_matWorld;
		mWorldMatrix.CreateTranslation(_Pos);
		mWorldMatrix.CreateFromQuaternion(_Rot);

		Matrix mRelativeWorld = mWorldMatrix * mParentWorldInv;
		
		Vector3 vRelativePos;
		Vector3 vRelativeScale;
		Quaternion qRelativeRot;
		mRelativeWorld.Decompose(vRelativeScale, qRelativeRot, vRelativePos);

		m_vRelativePos = vRelativePos;
		m_vRelativeRot = qRelativeRot.ToEuler();

		return;
	}

	m_vRelativePos = _Pos;
	m_vRelativeRot = _Rot.ToEuler();
}

void CTransform::BuildWorldMatrix()
{
	m_matWorldScale = XMMatrixIdentity();
	m_matWorldScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

	Matrix matRot = Matrix::CreateFromQuaternion(GetRelativeRot());

	Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);


	m_matWorld = m_matWorldScale * matRot * matTranslation;

	Vec3 vDefaultDir[3] = {
		  Vec3(1.f, 0.f, 0.f)
		, Vec3(0.f, 1.f, 0.f)
		, Vec3(0.f, 0.f, 1.f)
	};

	for (int i = 0; i < 3; ++i)
	{
		m_vWorldDir[i] = m_vRelativeDir[i] = XMVector3TransformNormal(vDefaultDir[i], matRot);
	}

	// 부모 오브젝트 확인
	CGameObject* pParent = GetOwner()->GetParent();
	if (pParent)
	{
		if (m_bAbsolute)
		{
			Matrix matParentWorld = pParent->Transform()->m_matWorld;
			Matrix matParentScale = pParent->Transform()->m_matWorldScale;
			Matrix matParentScaleInv = XMMatrixInverse(nullptr, matParentScale);

			// 월드 = 로컬월드 * 부모크기 역 * 부모 월드(크기/회전/이동)
			m_matWorld = m_matWorld * matParentScaleInv * matParentWorld;
		}
		else
		{
			m_matWorldScale = pParent->Transform()->m_matWorldScale;
			m_matWorld *= pParent->Transform()->m_matWorld;
		}


		for (int i = 0; i < 3; ++i)
		{
			m_vWorldDir[i] = XMVector3TransformNormal(vDefaultDir[i], m_matWorld);
			m_vWorldDir[i].Normalize();
		}
	}

	m_matWorldInv = XMMatrixInverse(nullptr, m_matWorld);
}

void CTransform::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_matWorld, sizeof(Matrix), 1, _File);
	fwrite(&m_vRelativePos	, sizeof(Vec3), 1, _File);
	fwrite(&m_vRelativeScale, sizeof(Vec3), 1, _File);
	fwrite(&m_vRelativeRot	, sizeof(Vec3), 1, _File);
	fwrite(&m_bAbsolute, sizeof(bool), 1, _File);
}

void CTransform::LoadFromLevelFile(FILE* _FILE)
{	
	fread(&m_matWorld, sizeof(Matrix), 1, _FILE);
	fread(&m_vRelativePos, sizeof(Vec3), 1, _FILE);
	fread(&m_vRelativeScale, sizeof(Vec3), 1, _FILE);
	fread(&m_vRelativeRot, sizeof(Vec3), 1, _FILE);
	fread(&m_bAbsolute, sizeof(bool), 1, _FILE);
}
