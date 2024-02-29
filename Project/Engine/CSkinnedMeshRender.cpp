#include "pch.h"
#include "CSkinnedMeshRender.h"

#include "CTransform.h"
#include "CStructuredBuffer.h"
#include "CBoneHolder.h"

CSkinnedMeshRender::CSkinnedMeshRender()
	: CRenderComponent(COMPONENT_TYPE::SKINNEDMESHRENDER)
	, m_vecBones()
	, m_bIsSet(false)
{
	m_pBoneTransforms = new CStructuredBuffer;
}

CSkinnedMeshRender::CSkinnedMeshRender(const CSkinnedMeshRender& _origin)
	: CRenderComponent(_origin)
	, m_vecBones(_origin.m_vecBones)
	, m_bIsSet(false)
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
	CBoneHolder* pBoneHolder = (CBoneHolder*)GetOwner()->GetComponentInParent(COMPONENT_TYPE::BONEHOLDER);
	if (!pBoneHolder) return;
	if (!pBoneHolder->IsReady()) return;

	auto boneNames = GetMesh()->GetBoneNames();
	if (boneNames.size() == 0) return;
	m_vecBones.clear();
	m_vecBones.resize(boneNames.size());
	for (size_t i = 0; i < boneNames.size(); i++)
	{
		m_vecBones[i] = pBoneHolder->GetBone(boneNames[i]);
	}

	m_pBoneTransforms->Clear();
	m_pBoneTransforms->Create(sizeof(Matrix), boneNames.size(), SB_TYPE::READ_ONLY, true, nullptr);

	m_bIsSet = true;
}

void CSkinnedMeshRender::finaltick()
{
	if (m_bIsSet) return;
	FindBones();
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
		m_pBoneTransforms->UpdateData(30, PIPELINE_STAGE::PS_VERTEX);
	}

	GetMaterial()->SetNumberOfBones(m_vecBones.size());

	GetMaterial()->UpdateData();
	GetMesh()->render();
}

void CSkinnedMeshRender::SetMesh(Ptr<CMesh> _Mesh)
{
	CRenderComponent::SetMesh(_Mesh);
	m_bIsSet = false;
}

void CSkinnedMeshRender::SaveToLevelFile(FILE* _File)
{
	CRenderComponent::SaveToLevelFile(_File);
}

void CSkinnedMeshRender::LoadFromLevelFile(FILE* _File)
{
	CRenderComponent::LoadFromLevelFile(_File);
	SetMesh(GetMesh());
}