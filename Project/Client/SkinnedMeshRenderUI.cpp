#include "pch.h"
#include "SkinnedMeshRenderUI.h"

#include <Engine/CSkinnedMeshRender.h>
#include "Engine\CGameObject.h"
#include <Engine/CResMgr.h>

#include "ImGuiMgr.h"
#include "ListUI.h"
#include "ComponentUI.h"

#include "TreeUI.h"

SkinnedMeshRenderUI::SkinnedMeshRenderUI()
	:ComponentUI("##SkinnedMeshRender", COMPONENT_TYPE::SKINNEDMESHRENDER)
{
	SetName("SkinnedMeshRender");
}

SkinnedMeshRenderUI::~SkinnedMeshRenderUI()
{
}
int SkinnedMeshRenderUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;
	const int buffsize = 250;
	char szBuff[buffsize] = {};

	Ptr<CMesh> pMesh = GetTarget()->SkinnedMeshRender()->GetMesh();
	Ptr<CMaterial> pMtrl = GetTarget()->SkinnedMeshRender()->GetMaterial();

	ImGui::Text("Mesh    ");
	ImGui::SameLine();
	GetResKey(pMesh.Get(), szBuff, buffsize);
	ImGui::InputText("##MeshName", szBuff, buffsize, ImGuiInputTextFlags_ReadOnly);

	// Mesh 드랍 체크
	if (ImGui::BeginDragDropTarget())
	{
		// 해당 노드에서 마우스 뗀 경우, 지정한 PayLoad 키값이 일치한 경우
		const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
		if (pPayLoad)
		{
			TreeNode* pNode = (TreeNode*)pPayLoad->Data;
			CRes* pRes = (CRes*)pNode->GetData();
			if (RES_TYPE::MESH == pRes->GetType())
			{
				GetTarget()->SkinnedMeshRender()->SetMesh((CMesh*)pRes);
			}
		}

		ImGui::EndDragDropTarget();
	}


	ImGui::SameLine();


	if (ImGui::Button("##MeshSelectBtn", ImVec2(18, 18)))
	{
		const map<wstring, Ptr<CRes>>& mapMesh = CResMgr::GetInst()->GetResources(RES_TYPE::MESH);

		ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
		pListUI->Reset("Mesh List", ImVec2(300.f, 500.f));
		for (const auto& pair : mapMesh)
		{
			pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
		}

		// 항목 선택시 호출받을 델리게이트 등록
		pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&SkinnedMeshRenderUI::SelectMesh);
	}

	ImGui::Text("Material");
	ImGui::SameLine();
	GetResKey(pMtrl.Get(), szBuff, buffsize);
	ImGui::InputText("##MtrlName", szBuff, buffsize, ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		// 해당 노드에서 마우스 뗀 경우, 지정한 PayLoad 키값이 일치한 경우
		const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
		if (pPayLoad)
		{
			TreeNode* pNode = (TreeNode*)pPayLoad->Data;
			CRes* pRes = (CRes*)pNode->GetData();
			if (RES_TYPE::MATERIAL == pRes->GetType())
			{
				GetTarget()->SkinnedMeshRender()->SetMaterial((CMaterial*)pRes);
			}
		}

		ImGui::EndDragDropTarget();
	}


	ImGui::SameLine();

	if (ImGui::Button("##MtrlSelectBtn", ImVec2(18, 18)))
	{
		const map<wstring, Ptr<CRes>>& mapMtrl = CResMgr::GetInst()->GetResources(RES_TYPE::MATERIAL);

		ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
		pListUI->Reset("Material", ImVec2(300.f, 500.f));
		for (const auto& pair : mapMtrl)
		{
			pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
		}

		// 항목 선택시 호출받을 델리게이트 등록
		pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&SkinnedMeshRenderUI::SelectMaterial);
	}

	//ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
	//ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
	//ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	//ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

	//if (pMtrl != nullptr)
	//{
	//	for (size_t i = 0; i < (UINT)TEX_TYPE::end; i++)
	//	{
	//		Ptr<CTexture> Texture = pMtrl.Get()->GetTexParam((TEX_PARAM)i);

	//		//if there is Texture
	//		if (Texture != nullptr)
	//		{
	//			//show Texture
	//			ImGui::Image((ImTextureID)Texture->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);

	//			//can Change Texture DragDrop
	//			if (ImGui::BeginDragDropTarget())
	//			{
	//				const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
	//				if (pPayLoad)
	//				{
	//					TreeNode* pNode = (TreeNode*)pPayLoad->Data;
	//					CRes* pRes = (CRes*)pNode->GetData();
	//					if (RES_TYPE::TEXTURE == pRes->GetType())
	//					{
	//						m_Idx = i;
	//						GetTarget()->SkinnedMeshRender()->SetTexture((CTexture*)pRes, m_Idx);
	//					}
	//				}
	//				ImGui::EndDragDropTarget();
	//			}
	//			ImGui::SameLine();
	//			if (ImGui::Button("##TextureSelectBtn", ImVec2(18, 18)))
	//			{
	//				//Get List about Tex
	//				const map<wstring, Ptr<CRes>>& Tex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

	//				ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
	//				pListUI->Reset("Texture", ImVec2(300.f, 500.f));
	//				for (const auto& pair : Tex)
	//				{
	//					pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
	//				}

	//				//Set Texture
	//				m_Idx = i;
	//				pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&SkinnedMeshRenderUI::SelectTexture);
	//			}


	//		}
	//		//if there is no Texture
	//		else
	//		{
	//			ImGui::Text("\nThere is no UI Texture please set the Texture");
	//			//give button to set Texture
	//			if (ImGui::Button("TextureSelectBtn", ImVec2(200, 18)))
	//			{
	//				//Get List about Tex
	//				const map<wstring, Ptr<CRes>>& Tex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

	//				ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
	//				pListUI->Reset("Texture", ImVec2(300.f, 500.f));
	//				for (const auto& pair : Tex)
	//				{
	//					pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
	//				}

	//				//Set Texture
	//				m_Idx = i;
	//				pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&SkinnedMeshRenderUI::SelectTexture);
	//			}
	//		}
	//	}
	//}

	ComponentUI::RemoveComponent();

	return TRUE;
}

void SkinnedMeshRenderUI::SelectMesh(DWORD_PTR _Key)
{
	string strKey = (char*)_Key;
	Ptr<CMesh> pMesh = CResMgr::GetInst()->FindRes<CMesh>(wstring(strKey.begin(), strKey.end()));
	GetTarget()->SkinnedMeshRender()->SetMesh(pMesh);
}

void SkinnedMeshRenderUI::SelectMaterial(DWORD_PTR _Key)
{
	string strKey = (char*)_Key;
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(wstring(strKey.begin(), strKey.end()));
	GetTarget()->SkinnedMeshRender()->SetMaterial(pMtrl);
}