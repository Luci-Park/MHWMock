#pragma once
#include "CRenderComponent.h"
class CTransform;
class CStructuredBuffer;
class CSkinnedMeshRender :
	public CRenderComponent
{
private:
	vector<CTransform*> m_vecBones;
	CStructuredBuffer*	m_pBoneTransforms;
	bool				m_bIsSet;
private:
	void FindBones();
public:
	virtual void finaltick() override;
	virtual void render() override;
	virtual void SetMesh(Ptr<CMesh> _Mesh) override;

	CLONE(CSkinnedMeshRender);

public:
	CSkinnedMeshRender();
	CSkinnedMeshRender(const CSkinnedMeshRender& _origin);
	~CSkinnedMeshRender();
};

