#pragma once
#include "CSingleton.h"

class CLayer;
class CCollider3D;

class CCollisionMgr :
	public CSingleton<CCollisionMgr>
{
	SINGLE(CCollisionMgr);

private:
	bool	m_bCollisionMap[MAX_LAYER][MAX_LAYER];
	bool	m_bCollisionChange;

	UINT	m_CollisionMatrix[MAX_LAYER];

public:
	void LayerCheck(UINT _left, UINT _right);
	void LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer);

	void LayerIgnore(UINT _left, UINT _right);
	void LayerIgnore(const wstring& _strLeftLayer, const wstring& _strRightLayer);

public:
	bool GetCollisionMap(UINT _rIdx, UINT _cIdx) { return m_bCollisionMap[_rIdx][_cIdx]; }
	void SetCollisionMap(UINT _rIdx, UINT _cIdx, bool _Check);

	bool GetCollisionChange() { return m_bCollisionChange; }
	void SetCollisionChange(bool _b) { m_bCollisionChange = _b; }

	void SetCollisionMapFromLevel(vector<UINT> _Matrix);
	vector<UINT> GetCollisionMatrixFromCollisionMgr();

public:
	void tick();

private:

};

