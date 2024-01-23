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

