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
	IsUsed = false;
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
	if (!IsUsed)
	{
		IsUsed = true;
		CreateColliderShape();
		EditConvexShape(Vector3(1.f, 1.f, 1.f));
	}

	assert(0 <= m_iCollisionCount);

	m_matCollider3D = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	m_matCollider3D *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	const Matrix& matWorld = Transform()->GetWorldMat();
	m_matCollider3D *= matWorld;

	// DebugShape 요청
	Vec4 vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	if (0 < m_iCollisionCount)
		vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	CRenderComponent* pRenderCom = GetOwner()->GetRenderComponent();

	// 렌더링 기능이 없는 오브젝트는 제외
	if (pRenderCom == nullptr
		|| pRenderCom->GetMesh() == nullptr)
		return;

	DrawDebugConvex3D(m_matCollider3D, vColor, 0.f);
	CRenderMgr::GetInst()->AddDebugShapeMesh3D(pRenderCom->GetMesh());
}



void CConvexCollider::CreateColliderShape()
{
	CRenderComponent* pRenderComponet = GetOwner()->GetRenderComponent();
	
	if (pRenderComponet == nullptr
		|| pRenderComponet->GetMesh() == nullptr)
		return;

	// 정점 정보, 인덱스 정보 가져오기.
	Ptr<CMesh> pMesh = pRenderComponet->GetMesh();

	void* pVtxSys = pMesh->GetVtxSys();
	void* pIdxSys = pMesh->GetIdxSys();
	UINT uVtxCount = pMesh->GetVtxCount();
	UINT uIdxCount = pMesh->GetVIdxCount();

	Vtx* pVtxArray = static_cast<Vtx*>(pVtxSys);

	vector<Vtx> vVtxData;
	vVtxData.assign(pVtxArray, pVtxArray + (uVtxCount));

	vector<Vec3> vVtxPosData;

	for (UINT i = 0; i < uVtxCount; ++i)
	{
		vVtxPosData.push_back(vVtxData[i].vPos);
	}

	CookingTriangleMesh(vVtxPosData.data(), uVtxCount, pIdxSys, uIdxCount);

	PxTriangleMeshGeometry geometry;

	geometry.triangleMesh = m_pTriangleMesh;
	geometry.scale = PxVec3(1.f, 1.f, 1.f);

	m_pShape = CPhysXMgr::GetInst()->GetPxPhysics()->createShape(geometry, *CPhysXMgr::GetInst()->GetDefaultMaterial());

	AddRigidActor();
}

void CConvexCollider::CookingTriangleMesh(void* _pPoints, UINT _VtxCount, void* _pIndices, UINT _IdxCount)
{
	PxTriangleMeshDesc triangleMeshDesc;

	triangleMeshDesc.points.count = _VtxCount;
	triangleMeshDesc.points.stride = sizeof(PxVec3);
	triangleMeshDesc.points.data = _pPoints;

	triangleMeshDesc.triangles.count = _IdxCount / 3;
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

void CConvexCollider::SaveToLevelFile(FILE* _File)
{
	CCollider3D::SaveToLevelFile(_File);
}

void CConvexCollider::LoadFromLevelFile(FILE* _File)
{
	CCollider3D::LoadFromLevelFile(_File);
}

