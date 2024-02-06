#pragma once
#include "CRenderComponent.h"

class CLandScape :
	public CRenderComponent
{
private:
	UINT			m_iFaceX;
	UINT			m_iFaceZ;

	Ptr<CTexture>	m_HeightMap;

public:
	void SetFace(UINT _iFaceX, UINT _iFaceZ);
	void SetHeightMap(Ptr<CTexture> _HeightMap) { m_HeightMap = _HeightMap; }

	int GetFaceX() { return m_iFaceX; }
	int GetFaceZ() { return m_iFaceZ; }
	Ptr<CTexture> GetHeightMap() { return m_HeightMap; }

	virtual void finaltick() override;
	virtual void render() override;

private:
	void CreateMesh();
	CLONE(CLandScape);
public:
	CLandScape();
	~CLandScape();
};

