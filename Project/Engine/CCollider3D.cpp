#include "pch.h"
#include "CCollider3D.h"

#include "CScript.h"
#include "components.h"
#include "CTransform.h"

#include "CRenderMgr.h"
#include "CPhysXMgr.h"

#include "CGameObject.h"

#include "CCollisionMgr.h"

CCollider3D::CCollider3D()
	:CComponent(COMPONENT_TYPE::COLLIDER3D)
	, m_ShapeType(SHAPE_TYPE::CAPSULE)
	, m_vOffsetPos(Vec3(0.f,0.f,0.f))
	, m_vOffsetScale(Vec3(1.f,1.f,1.f))
	, m_iCollisionCount(0)
	, m_eActorType(ACTOR_TYPE::END)
	, m_pMaterial(nullptr)
	, m_pRigidActor(nullptr)
	, m_pShape(nullptr)
	, m_bGround(false)
{
}

CCollider3D::~CCollider3D()
{
	if (m_pRigidActor != nullptr)
	{
		if (m_pRigidActor->getScene())
			m_pRigidActor->getScene()->removeActor(*m_pRigidActor);

		PX_RELEASE(m_pRigidActor);
	}
}

void CCollider3D::begin()
{
}

void CCollider3D::finaltick()
{
	/*if (m_eActorType == ACTOR_TYPE::DYNAMIC)
	{
		SetRigidDynamicLockFlag(true);
	}*/
}

void CCollider3D::SetGravity(bool _gravity)
{
	if (m_eActorType == ACTOR_TYPE::DYNAMIC)
	{
		if (_gravity)
			m_pRigidActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
		else
		{
			m_pRigidActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			m_pRigidActor->is<PxRigidDynamic>()->setLinearVelocity(PxVec3(0.f, 0.f, 0.f));
		}
	}
}

void CCollider3D::CreateRigidActor()
{
	// 만약 RigidActor가 존재한다면 삭제해줌.
	if (m_pRigidActor != nullptr )
	{
		if (m_pRigidActor->getScene())
			m_pRigidActor->getScene()->removeActor(*m_pRigidActor);

		PX_RELEASE(m_pRigidActor);
	}

	Vec3 vPos;
	Quaternion qRot;
	Vec3 vScale;

	if (Transform()->Decompose(vScale, qRot, vPos) == false)
		return;

	vPos.z = -vPos.z;
	qRot.z = -qRot.z;

	PxVec3 pxPos;
	PxQuat pxQuat;

	memcpy_s(&pxPos, sizeof(Vec3), &vPos, sizeof(Vec3));
	memcpy_s(&pxQuat, sizeof(Quaternion), &qRot, sizeof(Quaternion));


	if (m_eActorType == ACTOR_TYPE::DYNAMIC)
	{
		m_pRigidActor = CPhysXMgr::GetInst()->GetPxPhysics()->createRigidDynamic(physx::PxTransform(pxPos, pxQuat));
	
		m_pRigidActor->is<PxRigidDynamic>()->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
		m_pRigidActor->is<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
		m_pRigidActor->is<PxRigidDynamic>()->setAngularDamping(0.0f);
		m_pRigidActor->is<PxRigidDynamic>()->setMass(0.0f);

		m_pRigidActor->is<PxRigidDynamic>()->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
		m_pRigidActor->is<PxRigidDynamic>()->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
		m_pRigidActor->is<PxRigidDynamic>()->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
	}
	else
	{
		m_pRigidActor = CPhysXMgr::GetInst()->GetPxPhysics()->createRigidStatic(physx::PxTransform(pxPos, pxQuat));

		//m_pRigidActor->is<PxRigidBody>()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, false);
	}
	
	
	PxMaterial* material = CPhysXMgr::GetInst()->GetPxPhysics()->createMaterial(0.0f, 0.0f, 0.0f);
	m_pShape->setMaterials(&material, 1);

	m_pUserData.pCollider = this;
	m_pUserData.bGround = m_bGround;

	m_pRigidActor->userData = (void*)&m_pUserData;


	// 물체의 회전 관련 속성 비활성화
	// SetFilterData.
	UINT iLayerIdx = GetOwner()->GetLayerIndex();
	PxFilterData filter = CPhysXMgr::GetInst()->GetPxFilterData(iLayerIdx);
	m_pShape->setSimulationFilterData(filter);
	m_pShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);


	m_pRigidActor->attachShape(*m_pShape);

	if (m_eActorType == ACTOR_TYPE::DYNAMIC)
	{
		m_pRigidActor->is<PxRigidDynamic>()->setMass(1.f);
		m_pRigidActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	}
}

void CCollider3D::ChangeFilterData()
{
	UINT iLayerIdx = GetOwner()->GetLayerIndex();
	PxFilterData filter = CPhysXMgr::GetInst()->GetPxFilterData(iLayerIdx);

	for (PxU32 i = 0; i < m_pRigidActor->getNbShapes(); ++i) 
	{
		m_pRigidActor->detachShape(*m_pShape);

		m_pShape->setSimulationFilterData(filter);
		PxFilterData filterCheck = m_pShape->getSimulationFilterData();

		m_pRigidActor->attachShape(*m_pShape);
	}
}

void CCollider3D::EditCapsuleShape(float _radius, float _halfHeight)
{
	dynamic_cast<CCapsuleCollider*>(this)->SetRadius(_radius);
	dynamic_cast<CCapsuleCollider*>(this)->SetHalfHeight(_halfHeight);
	//Dettach shape from Actor
	m_pRigidActor->detachShape(*m_pShape);

	//GetGeometry
	PxGeometryHolder geoHolder = m_pShape->getGeometry();
	physx::PxGeometryType::Enum tpye = geoHolder.getType();

	Vec3 vPos;
	Quaternion qRot;
	Vec3 vScale;
	if (Transform()->Decompose(vScale, qRot, vPos) == false)
		return;

	_radius *= vScale.x / 2.f;
	_halfHeight	*= vScale.y / 2.f;

	//Edit Geometry
	if (tpye == physx::PxGeometryType::eCAPSULE)
	{
		PxCapsuleGeometry capGeo = geoHolder.capsule();
		capGeo.radius = PxReal(_radius);
		capGeo.halfHeight = PxReal(_halfHeight);
		m_pShape->setGeometry(capGeo);
	}

	//

	//attachShape
	m_pRigidActor->attachShape(*m_pShape);
}

void CCollider3D::EditBoxShape(Vec3 _halfExtents)
{
	dynamic_cast<CBoxCollider*>(this)->SetExtents(_halfExtents);
	//Dettach shape from Actor
	m_pRigidActor->detachShape(*m_pShape);

	//GetGeometry
	PxGeometryHolder geoHolder = m_pShape->getGeometry();
	physx::PxGeometryType::Enum tpye = geoHolder.getType();

	Vec3 vPos;
	Quaternion qRot;
	Vec3 vScale;
	if (Transform()->Decompose(vScale, qRot, vPos) == false)
		return;

	_halfExtents *= vScale;
	_halfExtents *= 0.5f;

	if (tpye == physx::PxGeometryType::eBOX)
	{
		PxBoxGeometry boxGeo = geoHolder.box();
		boxGeo.halfExtents = PxVec3(_halfExtents.x, _halfExtents.y, _halfExtents.z);
		m_pShape->setGeometry(boxGeo);
	}

	//attachShape
	m_pRigidActor->attachShape(*m_pShape);
}

void CCollider3D::EditConvexShape(Vec3 _scale)
{
	//Dettach shape from Actor
	m_pRigidActor->detachShape(*m_pShape);

	//GetGeometry
	PxGeometryHolder geoHolder = m_pShape->getGeometry();
	physx::PxGeometryType::Enum tpye = geoHolder.getType();

	Vec3 vPos;
	Quaternion qRot;
	Vec3 vScale;
	if (Transform()->Decompose(vScale, qRot, vPos) == false)
		return;

	_scale *= vScale;

	if (tpye == physx::PxGeometryType::eTRIANGLEMESH)
	{
		PxConvexMeshGeometry convexGeo = geoHolder.convexMesh();
		convexGeo.scale.scale = PxVec3(_scale.x, _scale.y, _scale.z);
		m_pShape->setGeometry(convexGeo);
	}

	//attachShape
	m_pRigidActor->attachShape(*m_pShape);
}

Vec3 CCollider3D::GetBoxExtents()
{
	return dynamic_cast<CBoxCollider*>(this)->GetExtents();
}

float CCollider3D::GetCapsuleRadius()
{
	return dynamic_cast<CCapsuleCollider*>(this)->GetRadius();
}

float CCollider3D::GetCapsuleHalfHeight()
{
	return dynamic_cast<CCapsuleCollider*>(this)->GetHeight();
}

void CCollider3D::DeleteRigidActor()
{
	if (m_pRigidActor != nullptr)
	{
		if (m_pRigidActor->getScene())
			m_pRigidActor->getScene()->removeActor(*m_pRigidActor);

		PX_RELEASE(m_pRigidActor);
	}
}

void CCollider3D::AddRigidActor()
{
	CreateRigidActor();

	CPhysXMgr::GetInst()->AddActor(*m_pRigidActor);
}

void CCollider3D::UpdateActorInfo()
{
	if (GetOwner()->IsDead() || GetOwner() == nullptr)
		return;

	// Transform의 데이터가 바뀌지 않았을경우 예외처리 .
	// ~~

	if (m_pRigidActor == nullptr)
		return;

	Vec3 vPos;
	Quaternion qRot;
	Vec3 vScale;

	m_matCollider3D.Decompose(vScale, qRot, vPos);

	PxVec3 pxPos;
	PxQuat pxQuat;

	memcpy_s(&pxPos, sizeof(Vec3), &vPos, sizeof(Vec3));
	memcpy_s(&pxQuat, sizeof(Quaternion), &qRot, sizeof(Quaternion));

	m_pRigidActor->setGlobalPose(physx::PxTransform(pxPos, pxQuat));

	return;

	//// 만약 중간에 충돌 할경우 위치를 멈추도록 구현.
	//PxVec3 vCurrPos = m_pRigidActor->getGlobalPose().p;

	//PxVec3 vRayDir = pxPos - vCurrPos;

	//float fDistance = vRayDir.magnitude();

	//vRayDir = vRayDir.getNormalized();

	//PxVec3 vOrigin = vCurrPos + m_pShape->getLocalPose().p;

	//PxRaycastBuffer rayCastBuffer;

	//PxScene* pScene = m_pRigidActor->getScene();

	//if (PxVec3(0) != vRayDir && pScene->raycast(vOrigin, vRayDir, 100.f, rayCastBuffer))
	//{
	//	if (rayCastBuffer.block.distance < fDistance)
	//	{
	//		pxPos = m_pRigidActor->getGlobalPose().p + vRayDir * (rayCastBuffer.block.distance - m_fOffsetRadius);
	//	}
	//}

	//m_pRigidActor->setGlobalPose(physx::PxTransform(pxPos, pxQuat));

}


void CCollider3D::SetGround(bool _Ground)
{
	m_bGround = _Ground;
	((pPXUSERDATA)(m_pRigidActor->userData))->bGround = m_bGround;

}

void CCollider3D::SetRigidDynamicLockFlag(bool _Lock)
{
	if (m_eActorType != ACTOR_TYPE::DYNAMIC)
		return;

	if (_Lock)
	{
		m_pRigidActor->is<PxRigidDynamic>()->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
		m_pRigidActor->is<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		//PxVec3 vVelocity = m_pRigidActor->is<PxRigidDynamic>()->getLinearVelocity();
		//m_pRigidActor->is<PxRigidDynamic>()->setLinearVelocity(vVelocity * 10000.f);

		//m_pRigidActor->is<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	}
}

void CCollider3D::OnCollisionEnter(CCollider3D* _Other)
{
	m_iCollisionCount += 1;

	// Script 호출
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnCollisionEnter(_Other);
	}
}

void CCollider3D::OnCollisionStay(CCollider3D* _Other)
{// Script 호출
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnCollisionStay(_Other);
	}
}

void CCollider3D::OnCollisionExit(CCollider3D* _Other)
{
	m_iCollisionCount -= 1;

	// Script 호출
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnCollisionExit(_Other);
	}
}

void CCollider3D::OnTriggerEnter(CCollider3D* _Other)
{
	int a = 0;
}

void CCollider3D::OnTriggerExit(CCollider3D* _Other)
{
	int a = 0;
}

void CCollider3D::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fwrite(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fwrite(&m_ShapeType, sizeof(UINT), 1, _File);
	fwrite(&m_eActorType, sizeof(UINT), 1, _File);
	fwrite(&m_iCollisionCount, sizeof(int), 1, _File);
	fwrite(&m_bGround, sizeof(bool), 1, _File);
}

void CCollider3D::LoadFromLevelFile(FILE* _File)
{
	fread(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fread(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fread(&m_ShapeType, sizeof(UINT), 1, _File);
	fread(&m_eActorType, sizeof(UINT), 1, _File);
	fread(&m_iCollisionCount, sizeof(int), 1, _File);
	fread(&m_bGround, sizeof(bool), 1, _File);
}


