#pragma once
#include "CRenderComponent.h"
class CTransform;
class CSkinnedMeshRender :
	public CRenderComponent
{
private:
	vector<CTransform> m_vecBones;
public:
	virtual void finaltick() override;
	virtual void render() override;

	CLONE(CSkinnedMeshRender);

public:
	CSkinnedMeshRender();
	~CSkinnedMeshRender();
};

