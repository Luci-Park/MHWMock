#include "pch.h"
#include "CCapsuleCollider.h"

#include "CCollider3D.h"

#include "CScript.h"
#include "components.h"
#include "CTransform.h"

#include "CRenderMgr.h"
#include "CPhysXMgr.h"

#include "CGameObject.h"

CCapsuleCollider::CCapsuleCollider()
{
}

CCapsuleCollider::~CCapsuleCollider()
{
}

void CCapsuleCollider::begin()
{
	CreateColliderShape();
}

void CCapsuleCollider::finaltick()
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

	DrawDebugCapsule3D(matWorld, vColor, 0.f);
}


void CCapsuleCollider::CreateColliderShape()
{
	Vec3 vPos;
	Quaternion qRot;
	Vec3 vScale;

	if (Transform()->Decompose(vScale, qRot, vPos) == false)
		return;

	vPos.z = -vPos.z;
	qRot.z = -qRot.z;

	float fRadius = Transform()->GetRelativeScale().x / 2.0f;
	float fHalfHeight = Transform()->GetRelativeScale().y / 2.0f;

	m_pMaterial = CPhysXMgr::GetInst()->GetDefaultMaterial();

	m_pShape = CPhysXMgr::GetInst()->GetPxPhysics()->createShape(PxCapsuleGeometry(vScale.x / 2.0f, vScale.y / 2.0f), *m_pMaterial);

	PxTransform relativePose(PxQuat(PxHalfPi, PxVec3(0.f, 0.f, 1.f)));

	m_pShape->setLocalPose(relativePose);

	AddRigidActor();
}

