#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CCollider3D.h"
#include "CPhysXMgr.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
	, m_bMatrixChange{}
{

}


CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
}


void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	PxFilterData rFilter = CPhysXMgr::GetInst()->GetPxFilterData(iRow);
	PxFilterData cFilter = CPhysXMgr::GetInst()->GetPxFilterData(iCol);

	rFilter.word1 |= (1 << iCol + 1);
	cFilter.word1 |= (1 << iRow + 1);

	CPhysXMgr::GetInst()->SetPxFilterData(rFilter, iRow);
	CPhysXMgr::GetInst()->SetPxFilterData(cFilter, iCol);
}

void CCollisionMgr::LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	CLayer* pLeft = pCurLevel->FindLayerByName(_strLeftLayer);
	CLayer* pRight = pCurLevel->FindLayerByName(_strRightLayer);

	LayerCheck(pLeft->GetLayerIndex(), pRight->GetLayerIndex());
}

