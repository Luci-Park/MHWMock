#pragma once
#include "CRenderComponent.h"
class CTransform;
class CStructuredBuffer;
class CSkinnedMeshRender :
	public CRenderComponent
{
private:
	vector<CTransform*> m_vecBones;
	CStructuredBuffer* m_pBoneMatBuffer;
public:
	void FindBones();
public:
	virtual void finaltick() override;
	virtual void render() override;

	CLONE(CSkinnedMeshRender);

public:
	CSkinnedMeshRender();
	~CSkinnedMeshRender();
};

