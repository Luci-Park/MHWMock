#pragma once
#include <Engine\CResMgr.h>

class CGameObjectEx;

class CEditorObjMgr
	: public CSingleton<CEditorObjMgr>
{
	SINGLE(CEditorObjMgr);
private:
	vector<CGameObjectEx*>	m_vecEditorObj;

	CGameObjectEx*			m_DebugShape[(UINT)SHAPE_TYPE::END];
	vector<tDebugShapeInfo> m_DebugShapeInfo;
	
	vector<tDebugShapeInfo3D>  m_DebugShapeInfo3D;
	vector<Ptr<CMesh>>			m_DebugShapeMesh3D;

	bool									m_bUseDebugObj;

public:
	void init();
	void progress();

private:
	void tick();
	void render();
};

