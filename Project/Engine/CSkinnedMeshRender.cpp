#include "pch.h"
#include "CSkinnedMeshRender.h"

#include "CTransform.h"
#include "CStructuredBuffer.h"

CSkinnedMeshRender::CSkinnedMeshRender()
	: CRenderComponent(COMPONENT_TYPE::SKINNEDMESHRENDER)
	, m_vecBones()
{
	m_pBoneTransforms = new CStructuredBuffer;
}

CSkinnedMeshRender::CSkinnedMeshRender(const CSkinnedMeshRender& _origin)
	: CRenderComponent(_origin)
	, m_vecBones(_origin.m_vecBones)
{
	m_pBoneTransforms = new CStructuredBuffer;
}

CSkinnedMeshRender::~CSkinnedMeshRender()
{
	if (nullptr != m_pBoneTransforms)
		delete m_pBoneTransforms;
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
	m_pBoneTransforms->Clear();
	m_pBoneTransforms->Create(sizeof(Matrix), boneNames.size(), SB_TYPE::READ_ONLY, true, nullptr);
}

void CSkinnedMeshRender::finaltick()
{
}

void CSkinnedMeshRender::render()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	Transform()->UpdateData();

	if (m_vecBones.size() > 0)
	{
		vector<Matrix> vecBoneTransforms(m_vecBones.size());
		for (int i = 0; i < m_vecBones.size(); i++)
		{
			vecBoneTransforms[i] = m_vecBones[i]->GetWorldMat().Transpose();

		}
		m_pBoneTransforms->SetData(vecBoneTransforms.data());
		//m_pBoneTransforms->UpdateData(30, PIPELINE_STAGE::PS_VERTEX);
	}

	GetMaterial()->SetNumberOfBones(m_vecBones.size());
	GetMaterial()->UpdateData();
	GetMesh()->render();
}

