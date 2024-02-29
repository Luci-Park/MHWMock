#pragma once
#include "CRenderComponent.h"
class CTransform;
class CStructuredBuffer;
class CSkinnedMeshRender :
	public CRenderComponent
{
private:
	vector<CTransform*>		m_vecBones;
	CStructuredBuffer*		m_pBoneTransforms;
	bool					m_bIsSet;
	vector<Ptr<CTexture>>	m_Texture;
private:
	void FindBones();
public:
	virtual void finaltick() override;
	virtual void render() override;
	virtual void SetMesh(Ptr<CMesh> _Mesh) override;
	virtual void SetTexture(Ptr<CTexture> _Texture, UINT _Indx);

	CLONE(CSkinnedMeshRender);

	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _File) override;
public:
	CSkinnedMeshRender();
	CSkinnedMeshRender(const CSkinnedMeshRender& _origin);
	~CSkinnedMeshRender();
};

