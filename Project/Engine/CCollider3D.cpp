#include "pch.h"
#include "CCollider3D.h"

#include "CScript.h"
#include "components.h"
#include "CTransform.h"

#include "CRenderMgr.h"
#include "CPhysXMgr.h"

#include "CGameObject.h"

CCollider3D::CCollider3D()
	:CComponent(COMPONENT_TYPE::COLLIDER3D)
	, m_ShapeType(SHAPE_TYPE::CAPSULE)
	, m_bAbsolute(false)
	, m_iCollisionCount(0)
	, m_bIsBegin(true)
{
}

CCollider3D::~CCollider3D()
{
}

void CCollider3D::begin()
{
	CreateColliderShape();
}

void CCollider3D::finaltick()
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

	// DebugShape 요청
	Vec4 vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	if (0 < m_iCollisionCount)
		vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	if (m_ShapeType == SHAPE_TYPE::CAPSULE)
	{
		DrawDebugCapsule3D(matWorld, vColor, 0.f);
	}
	else if (m_ShapeType == SHAPE_TYPE::CONVEX)
	{
		CRenderComponent* pRenderCom = GetOwner()->GetRenderComponent();

		// 렌더링 기능이 없는 오브젝트는 제외
		if (pRenderCom == nullptr
			|| pRenderCom->GetMesh() == nullptr )
			return;

		DrawDebugConvex3D(matWorld, vColor, 0.f);
		CRenderMgr::GetInst()->AddDebugShapeMesh3D(pRenderCom->GetMesh());
	}
}

void CCollider3D::CreateColliderShape()
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

	/*if (m_bRigid)
		m_pRigidActor = Physics::GetPxPhysics()->createRigidDynamic(physx::PxTransform(pxPos, pxQuat));
	else
		m_pRigidActor = Physics::GetPxPhysics()->createRigidStatic(physx::PxTransform(pxPos, pxQuat));*/

	m_pRigidActor = CPhysXMgr::GetInst()->GetPxPhysics()->createRigidDynamic(physx::PxTransform(pxPos, pxQuat));
	m_pUserData.pCollider = this;
	m_pUserData.bGround = false;

	m_pRigidActor->userData = (void*)&m_pUserData;

	// SetFilterData.
	UINT iLayerIdx = GetOwner()->GetLayerIndex();
	PxFilterData filter = CPhysXMgr::GetInst()->GetPxFilterData(iLayerIdx);
	m_pShape->setSimulationFilterData(filter);

	m_pShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);

	m_pRigidActor->attachShape(*m_pShape);
	m_pRigidActor->setMass(1.f);
}

void CCollider3D::ChangeFilterData()
{
	// 여기서 뭔가 ACTOR을 삭제하든 FILTER를 바꾸든 뭔가 해야함..

	// SetFilterData. (에러.) FILTER를 잘 가져오긴 하는데 filtershader에서 수정되지 않음..;;
	UINT iLayerIdx = GetOwner()->GetLayerIndex();
	PxFilterData filter = CPhysXMgr::GetInst()->GetPxFilterData(iLayerIdx);
	m_pShape->setSimulationFilterData(filter);
	m_pRigidActor->attachShape(*m_pShape);
}


void CCollider3D::AddRigidActor()
{
	CreateRigidActor();

	CPhysXMgr::GetInst()->AddActor(*m_pRigidActor);
}

void CCollider3D::UpdateActorInfo()
{
	if (GetOwner() == nullptr)
		return;
	// Transform의 데이터가 바뀌지 않았을경우 예외처리 .
	// ~~

	if (m_pRigidActor == nullptr)
		return;

	Vec3 vPos;
	Quaternion qRot;
	Vec3 vScale;

	if (Transform()->Decompose(vScale, qRot, vPos) == false)
		return;

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
	
}

void CCollider3D::OnTriggerExit(CCollider3D* _Other)
{
	
}

void CCollider3D::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fwrite(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fwrite(&m_bAbsolute, sizeof(bool), 1, _File);
}

void CCollider3D::LoadFromLevelFile(FILE* _File)
{
	fread(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fread(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fread(&m_bAbsolute, sizeof(bool), 1, _File);
}


