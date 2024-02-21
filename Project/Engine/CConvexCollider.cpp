#include "pch.h"
#include "CConvexCollider.h"

#include "CCollider3D.h"

#include "CScript.h"
#include "components.h"
#include "CTransform.h"`
#include "CRenderComponent.h"

#include "CRenderMgr.h"
#include "CPhysXMgr.h"

#include "CGameObject.h"

CConvexCollider::CConvexCollider()
{
	m_ShapeType = SHAPE_TYPE::CONVEX;
}

CConvexCollider::~CConvexCollider()
{
}

void CConvexCollider::begin()
{
	CreateColliderShape();
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
	Ptr<CMesh> pMesh = pRenderComponet->GetMesh();

	vector<Vector3> Verticies = pMesh->GetVerticies();
	vector<UINT> Indicies= pMesh->GetIndicies();
	UINT uNumPoint = pMesh->GetVtxCount();
	UINT uNumFace = pMesh->GetVIdxCount();
	
	CookingTriangleMesh(Verticies.data(), uNumPoint, Indicies.data(), uNumFace);
	//CookingTriangleMesh(pMesh->GetVtxSys(), uNumPoint, pMesh->GetIdxSys(), uNumFace);

	PxTriangleMeshGeometry geometry;

	geometry.triangleMesh = m_pTriangleMesh;
	geometry.scale = PxVec3(1.f, 1.f, 1.f);

	m_pShape = CPhysXMgr::GetInst()->GetPxPhysics()->createShape(geometry, *CPhysXMgr::GetInst()->GetDefaultMaterial());

	AddRigidActor();
}

void CConvexCollider::CookingTriangleMesh(void* _pPoints, UINT _nNumPoint, void* _pIndices, UINT _nNumFace)
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

	//bool bTemp = PxValidateTriangleMesh(CPhysXMgr::GetInst()->GetPxPhysics()->getTolerancesScale(), triangleMeshDesc);

	bool status = PxCookTriangleMesh(CPhysXMgr::GetInst()->GetPxPhysics()->getTolerancesScale(), triangleMeshDesc, writeBuffer, &eResult);

	if (false == status)
	{
		return;
	}

	PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());

	m_pTriangleMesh = CPhysXMgr::GetInst()->GetPxPhysics()->createTriangleMesh(readBuffer);
}