#pragma once
#include "CRenderComponent.h"
class CSkinnedMeshRender :
	public CRenderComponent
{
public:
	virtual void finaltick() override;
	virtual void render() override;

	CLONE(CSkinnedMeshRender);

public:
	CSkinnedMeshRender();
	~CSkinnedMeshRender();
};

