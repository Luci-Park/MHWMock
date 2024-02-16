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
	// Layer m_matrix�� �������� PxFilterData ����.
	// �������� �ִ� FilterData�� ����.
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

					// ��� ���� �Դٸ� Layer iRow, iCol�� �浹.
					// FIlterData.word1 �������ֱ�.
					//PxFilterData filter = CPhysXMgr::GetInst()->GetPxFilterData(iCol);
					//filter.word1 = ~~

					//PxFilterData filterData;
					//filterData.word0 = 1; // �׷� 1�� ����
					//filterData.word1 = 1 << 1; // �׷� 2���� �浹 ���
					//filterData.word1 = (1 << 1) | (1 << 3); // �׷� 1�� �׷� 3���� �浹 ���
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
