#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"
#include "CAnimator2D.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)		
{
}

CMeshRender::CMeshRender(CMeshRender& _origin)
	: CRenderComponent(_origin)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::finaltick()
{
}

void CMeshRender::render()
{	
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	// Transform �� UpdateData ��û
	Transform()->UpdateData();

	// Animator2D ������Ʈ�� �ִٸ�
	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}

	GetMaterial()->SetNumberOfBones(0);
	// ���� ������Ʈ
	GetMaterial()->UpdateData();

	// ����
	GetMesh()->render();


	// Animation ���� ���� ����
	if (Animator2D())
		Animator2D()->Clear();
}