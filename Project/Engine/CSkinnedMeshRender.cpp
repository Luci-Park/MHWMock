#include "pch.h"
#include "CSkinnedMeshRender.h"

#include "CTransform.h"
#include "CStructuredBuffer.h"

CSkinnedMeshRender::CSkinnedMeshRender()
	:CRenderComponent(COMPONENT_TYPE::SKINNEDMESHRENDER)
{
}

CSkinnedMeshRender::~CSkinnedMeshRender()
{

}

void CSkinnedMeshRender::FindBones()
{
	if (GetMesh() == nullptr) return;
	
	auto boneNames = GetMesh()->GetBoneNames();
	if (boneNames.size() == 0) return;

	CGameObject* pRoot = GetOwner()->GetRoot();
	m_vecBones.resize(boneNames.size());
	for (size_t i = 0; i < boneNames.size(); i++)
	{
		CGameObject* pObj = pRoot->FindChildByName(boneNames[i]);
		assert(pObj);
		m_vecBones[i] = pObj->Transform();
	}
}

void CSkinnedMeshRender::finaltick()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	Transform()->UpdateData();

	// 재질 업데이트
	GetMaterial()->UpdateData();

	// 렌더
	GetMesh()->render();

}

void CSkinnedMeshRender::render()
{
}

