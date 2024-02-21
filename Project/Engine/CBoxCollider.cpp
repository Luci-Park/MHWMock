#include "pch.h"
#include "CBoxCollider.h"

#include "CCollider3D.h"

#include "CScript.h"
#include "components.h"
#include "CTransform.h"

#include "CRenderMgr.h"
#include "CPhysXMgr.h"

#include "CGameObject.h"

CBoxCollider::CBoxCollider()
{
}

CBoxCollider::~CBoxCollider()
{
}


void CBoxCollider::begin()
{
	CreateColliderShape();
}

void CBoxCollider::finaltick()
{
	assert(0 <= m_iCollisionCount);

	m_matCollider3D = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	m_matCollider3D *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	const Matrix& matWorld = Transform()->GetWorldMat();

	if (m_bAbsolute)
	{
		Matrix matParentScaleInv = XMMatrixInverse(nullptr, Transform()->GetWorldScaleMat());
		m_matCollider3D = m_matCollider3D * matParentScaleInv * matWorld;
	}
	else
	{
		m_matCollider3D *= matWorld;
	}

	// DebugShape ฟไรป
	Vec4 vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	if (0 < m_iCollisionCount)
		vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	DrawDebugCube(matWorld, vColor, 0.f);
}

void CBoxCollider::CreateColliderShape()
{
	Vec3 vPos;
	Quaternion qRot;
	Vec3 vScale;

	if (Transform()->Decompose(vScale, qRot, vPos) == false)
		return;

	PxVec3 vHalfExtent(0.f, 0.f, 0.f);
	memcpy_s(&vHalfExtent, sizeof(Vec3), &vScale, sizeof(Vec3));
	vHalfExtent = vHalfExtent * 0.5f;

	m_pMaterial = CPhysXMgr::GetInst()->GetDefaultMaterial();

	//Create BoxShape
	m_pShape = CPhysXMgr::GetInst()->GetPxPhysics()->createShape(physx::PxBoxGeometry(vHalfExtent), *m_pMaterial, true);

	AddRigidActor();
}
