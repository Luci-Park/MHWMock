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
	// Layer m_matrix를 바탕으로 PxFilterData 수정.
	// 변경점이 있는 FilterData만 수정.
	if (m_bMatrixChange)
	{
		for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
		{
			if (m_bMatrixChange[iRow])
			{
				for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
				{
					if (!(m_matrix[iRow] & (1 << iCol)))
						continue;

					// 요기 까지 왔다면 Layer iRow, iCol은 충돌.
					// FIlterData.word1 수정해주기.
					//PxFilterData filter = CPhysXMgr::GetInst()->GetPxFilterData(iCol);
					//filter.word1 = ~~

					//PxFilterData filterData;
					//filterData.word0 = 1; // 그룹 1에 속함
					//filterData.word1 = 1 << 1; // 그룹 2와의 충돌 허용
					//filterData.word1 = (1 << 1) | (1 << 3); // 그룹 1과 그룹 3과의 충돌 허용
				}
			}
			m_bMatrixChange[iRow] = false;
		}
	
	
	}


}


void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);

	m_bMatrixChange[iRow] = true;
}

void CCollisionMgr::LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	CLayer* pLeft = pCurLevel->FindLayerByName(_strLeftLayer);
	CLayer* pRight = pCurLevel->FindLayerByName(_strRightLayer);

	LayerCheck(pLeft->GetLayerIndex(), pRight->GetLayerIndex());
}
