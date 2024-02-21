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



	//CookingTriangleMesh();

	PxTriangleMeshGeometry geometry;

	geometry.triangleMesh = m_pTriangleMesh;
	geometry.scale = PxVec3(0.001f, 0.001f, 0.001f);

	m_pShape = CPhysXMgr::GetInst()->GetPxPhysics()->createShape(geometry, *CPhysXMgr::GetInst()->GetDefaultMaterial(), true);

	AddRigidActor();
}

void CConvexCollider::CookingTriangleMesh(Vector3* _pPoints, UINT _nNumPoint, UINT* _pIndices, UINT _nNumFace)
{

}