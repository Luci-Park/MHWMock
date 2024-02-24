#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CCollider3D.h"
#include "CPhysXMgr.h"

CCollisionMgr::CCollisionMgr()
	: m_bCollisionMap{}
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

void CCollisionMgr::LayerIgnore(UINT _left, UINT _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	PxFilterData rFilter = CPhysXMgr::GetInst()->GetPxFilterData(iRow);
	PxFilterData cFilter = CPhysXMgr::GetInst()->GetPxFilterData(iCol);

	PxU32 CheckRow = (1 << iRow + 1);
	PxU32 CheckCol = (1 << iCol + 1);

	PxU32 reverseRow = ~(1 << iRow + 1);
	PxU32 reverseCol = ~(1 << iCol + 1);

	rFilter.word1 &= reverseCol;
	cFilter.word1 &= reverseRow;

	CPhysXMgr::GetInst()->SetPxFilterData(rFilter, iRow);
	CPhysXMgr::GetInst()->SetPxFilterData(cFilter, iCol);
}

void CCollisionMgr::LayerIgnore(const wstring& _strLeftLayer, const wstring& _strRightLayer)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	CLayer* pLeft = pCurLevel->FindLayerByName(_strLeftLayer);
	CLayer* pRight = pCurLevel->FindLayerByName(_strRightLayer);

	LayerIgnore(pLeft->GetLayerIndex(), pRight->GetLayerIndex());
}

void CCollisionMgr::SetCollisionMap(UINT _rIdx, UINT _cIdx, bool _Check)
{ 
	if (m_bCollisionMap[_rIdx][_cIdx] == _Check)
		return;

	m_bCollisionMap[_rIdx][_cIdx] = _Check; 

	if (_Check)
	{
		LayerCheck(_rIdx, _cIdx);
	}
	else
	{
		LayerIgnore(_rIdx, _cIdx);
	}

	m_bCollisionChange = true;
}