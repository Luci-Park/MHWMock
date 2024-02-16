#pragma once
#include "CSingleton.h"

class CLayer;
class CCollider3D;

class CCollisionMgr :
    public CSingleton<CCollisionMgr>
{
	SINGLE(CCollisionMgr);
private:
	UINT					m_matrix[MAX_LAYER];
	bool					m_bMatrixChange;

public:
	void LayerCheck(UINT _left, UINT _right);
	void LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer);

	void Clear()
	{
		memset(m_matrix, 0, sizeof(UINT) * MAX_LAYER);
	}

public:
	void tick();

private:

};

