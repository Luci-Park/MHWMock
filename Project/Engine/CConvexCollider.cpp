#include "pch.h"
#include "CConvexCollider.h"

#include "CCollider3D.h"

#include "CScript.h"
#include "components.h"
#include "CTransform.h"
#include "CRenderComponent.h"

#include "CRenderMgr.h"
#include "CPhysXMgr.h"

#include "CGameObject.h"

CConvexCollider::CConvexCollider()
{
}

CConvexCollider::~CConvexCollider()
{
}

void CConvexCollider::begin()
{
}

void CConvexCollider::finaltick()
{
}



void CConvexCollider::CreateColliderShape()
{
	CRenderComponent* pRenderComponet = GetOwner()->GetRenderComponent();
	
	if (pRenderComponet == nullptr
		|| pRenderComponet->GetMesh() == nullptr)
		return;

	// 정점 정보, 인덱스 정보 가져오기.


	//CookingTriangleMesh();

	PxTriangleMeshGeometry geometry;

	geometry.triangleMesh = m_pTriangleMesh;
	geometry.scale = PxVec3(0.001f, 0.001f, 0.001f);

	m_pShape = CPhysXMgr::GetInst()->GetPxPhysics()->createShape(geometry, *CPhysXMgr::GetInst()->GetDefaultMaterial(), true);

	AddRigidActor();
}

void CConvexCollider::CookingTriangleMesh(Vector3* _pPoints, UINT _nNumPoint, UINT* _pIndices, UINT _nNumFace)
{
	PxTriangleMeshDesc triangleMeshDesc;

	triangleMeshDesc.points.count = _nNumPoint;
	triangleMeshDesc.points.stride = sizeof(PxVec3);
	triangleMeshDesc.points.data = _pPoints;

	triangleMeshDesc.triangles.count = _nNumFace / 3;
	triangleMeshDesc.triangles.stride = 3 * sizeof(PxU32);
	triangleMeshDesc.triangles.data = _pIndices;

	triangleMeshDesc.flags = PxMeshFlags(0);

	PxDefaultMemoryOutputStream writeBuffer;

	PxTriangleMeshCookingResult::Enum eResult;

	bool bTemp = PxValidateTriangleMesh(CPhysXMgr::GetInst()->GetPxPhysics()->getTolerancesScale(), triangleMeshDesc);
	bool status = PxCookTriangleMesh(CPhysXMgr::GetInst()->GetPxPhysics()->getTolerancesScale(), triangleMeshDesc, writeBuffer, &eResult);

	if (false == status)
	{
		return;
	}

	PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());

	m_pTriangleMesh = CPhysXMgr::GetInst()->GetPxPhysics()->createTriangleMesh(readBuffer);
}