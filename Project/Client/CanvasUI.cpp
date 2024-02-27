#include "pch.h"
#include "CanvasUI.h"

#include "Engine\CMesh.h"
#include "Engine\CMaterial.h"
#include "Engine\CGameObject.h"
#include "Engine\CMeshRender.h"
#include "Engine\CRes.h"
#include "Engine\CResMgr.h"
#include "Engine\CCanvas.h"

#include "ImGuiMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

CanvasUI::CanvasUI()
	: ComponentUI("##CANVAS",COMPONENT_TYPE::CANVAS)
{
	SetName("CANVAS");
}

CanvasUI::~CanvasUI()
{
}

int CanvasUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;

	const int buffsize = 250;
	char szBuff[buffsize] = {};

	Ptr<CMesh> pMesh = GetTarget()->GetRenderComponent()->GetMesh();
	Ptr<CMaterial> pMtrl = GetTarget()->GetRenderComponent()->GetMaterial();

	ImGui::Text("Mesh    ");
	ImGui::SameLine();
	GetResKey(pMesh.Get(), szBuff, buffsize);
	ImGui::InputText("##MeshName", szBuff, buffsize, ImGuiInputTextFlags_ReadOnly);

	// Mesh ��� üũ
	if (ImGui::BeginDragDropTarget())
	{
		// �ش� ��忡�� ���콺 �� ���, ������ PayLoad Ű���� ��ġ�� ���
		const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
		if (pPayLoad)
		{
			TreeNode* pNode = (TreeNode*)pPayLoad->Data;
			CRes* pRes = (CRes*)pNode->GetData();
			if (RES_TYPE::MESH == pRes->GetType())
			{
				GetTarget()->GetRenderComponent()->SetMesh((CMesh*)pRes);
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

		// �׸� ���ý� ȣ����� ��������Ʈ ���
		pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&CanvasUI::SelectMesh);
	}

	ImGui::Text("Material");
	ImGui::SameLine();
	GetResKey(pMtrl.Get(), szBuff, buffsize);
	ImGui::InputText("##MtrlName", szBuff, buffsize, ImGuiInputTextFlags_ReadOnly);

	ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

	if (ImGui::BeginDragDropTarget())
	{
		// �ش� ��忡�� ���콺 �� ���, ������ PayLoad Ű���� ��ġ�� ���
		const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
		if (pPayLoad)
		{
			TreeNode* pNode = (TreeNode*)pPayLoad->Data;
			CRes* pRes = (CRes*)pNode->GetData();
			if (RES_TYPE::MATERIAL == pRes->GetType())
			{
				GetTarget()->GetRenderComponent()->SetMaterial((CMaterial*)pRes);
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

		// �׸� ���ý� ȣ����� ��������Ʈ ���
		pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&CanvasUI::SelectMaterial);
	}

	if (pMtrl != nullptr)
	{
		//if there is Texture
		Ptr<CTexture> UITexture = GetTarget()->Canvas()->GetUITexture();

		
		if (UITexture != nullptr)
		{
			//show Texture
			ImGui::Image((ImTextureID)UITexture->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);

			//can Change Texture DragDrop
			if (ImGui::BeginDragDropTarget())
			{
				const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
				if (pPayLoad)
				{
					TreeNode* pNode = (TreeNode*)pPayLoad->Data;
					CRes* pRes = (CRes*)pNode->GetData();
					if (RES_TYPE::TEXTURE == pRes->GetType())
					{
						GetTarget()->Canvas()->SetUITexture((CTexture*)pRes);
					}
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::SameLine();
			if (ImGui::Button("##TextureSelectBtn", ImVec2(18, 18)))
			{
				//Get List about Tex
				const map<wstring, Ptr<CRes>>& Tex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

				ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
				pListUI->Reset("Texture", ImVec2(300.f, 500.f));
				for (const auto& pair : Tex)
				{
					pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
				}

				//Set Texture
				pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&CanvasUI::SelectTexture);
			}


		}
		//if there is no Texture
		else
		{
			ImGui::Text("\nThere is no UI Texture please set the Texture");
			//give button to set Texture
			if (ImGui::Button("TextureSelectBtn", ImVec2(200, 18)))
			{
				//Get List about Tex
				const map<wstring, Ptr<CRes>>& Tex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

				ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
				pListUI->Reset("Texture", ImVec2(300.f, 500.f));
				for (const auto& pair : Tex)
				{
					pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
				}

				//Set Texture
				pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&CanvasUI::SelectTexture);
			}
		}
	}


	if (ImGui::BeginPopupContextItem("Remove Component"))
	{
		ImGui::Text("Really want to remove Component?");
		if (ImGui::Button("Yes"))
		{
			GetTarget()->DeleteComponent(this->GetComponentType());
		}
		ImGui::SameLine();
		if (ImGui::Button("NO"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}


	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
	ImGui::Button("Remove");
	ImGui::PopStyleColor(1);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Remove this Component");
	ImGui::OpenPopupOnItemClick("Remove Component", ImGuiPopupFlags_MouseButtonRight);

	return TRUE;
}

void CanvasUI::SelectMesh(DWORD_PTR _Key)
{
	string strKey = (char*)_Key;
	Ptr<CMesh> pMesh = CResMgr::GetInst()->FindRes<CMesh>(wstring(strKey.begin(), strKey.end()));
	GetTarget()->GetRenderComponent()->SetMesh(pMesh);
}

void CanvasUI::SelectMaterial(DWORD_PTR _Key)
{
	string strKey = (char*)_Key;
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(wstring(strKey.begin(), strKey.end()));
	GetTarget()->GetRenderComponent()->SetMaterial(pMtrl);
}

void CanvasUI::SelectTexture(DWORD_PTR _Key)
{
	string strKey = (char*)_Key;
	Ptr<CTexture> tex = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));
	GetTarget()->Canvas()->SetUITexture(tex);
}
