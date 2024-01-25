#include "pch.h"
#include "TransformUI.h"
#include "OutlinerUI.h"
#include "Engine\CRenderMgr.h"
#include "ImGuizmo.h"
#include "Engine\CCamera.h"

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>

TransformUI::TransformUI()
	: ComponentUI("##Transform", COMPONENT_TYPE::TRANSFORM)	
{
	SetName("Transform");
}

TransformUI::~TransformUI()
{
}

void TransformUI::Gizmo()
{
    CGameObject* selectedObj = GetTarget();

    if (nullptr != selectedObj)
    {

        ImGuizmo::SetOrthographic(false);
        //ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
        //ImGuizmo::SetDrawlist(ImGui::GetForegroundDrawList());
        ImGuizmo::SetDrawlist();

        //Set Gizmo Viewport
        //1280 * 768
        //float x = ImGui::GetMainViewport()->WorkPos.x;
        //float y = ImGui::GetMainViewport()->WorkPos.y;
        //float windowWidth = ImGui::GetMainViewport()->WorkSize.x;
        //float windowHeight = ImGui::GetMainViewport()->WorkSize.y;

        float x = ImGui::GetWindowPos().x;
        float y = ImGui::GetWindowPos().y;
        float windowWidth = ImGui::GetWindowSize().x;
        float windowHeight = ImGui::GetWindowSize().y;


        ImGuizmo::SetRect(x, y, windowWidth, windowHeight);


        //GetCamera Matrix
        CCamera* editorCamera = CRenderMgr::GetInst()->GetEditorCamera();
        XMMATRIX viewMat = editorCamera->GetViewMat();
        XMMATRIX projMat = editorCamera->GetProjMat();

        XMFLOAT4X4 v = change_mat(viewMat);
        XMFLOAT4X4 p = change_mat(projMat);

        //Get ojectTransformMatrix
        auto objTransform = selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform();
        XMMATRIX objMat = objTransform->GetWorldMat();
        DirectX::XMFLOAT4X4 w = change_mat(objMat);

        XMMATRIX viewInv = editorCamera->GetViewInvMat();
        XMFLOAT4X4 iv = change_mat(viewInv);

        //Render Gizmo
        ImGuizmo::Manipulate(*v.m, *p.m, ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, *w.m);
        if(ImGuizmo::IsOver())
        {
            int a = 0;
        }

        if (ImGuizmo::IsUsing())
        {
            objTransform->SetWorldMat(w);
        }

    }
}

int TransformUI::render_update()
{
    //Gizmo();

	if (FALSE == ComponentUI::render_update())
		return FALSE;

	Vec3 vPos = GetTarget()->Transform()->GetRelativePos();
	Vec3 vScale = GetTarget()->Transform()->GetRelativeScale();
	Vec3 vRotation = GetTarget()->Transform()->GetRelativeRot();
	vRotation = (vRotation / XM_PI) * 180.f;

	ImGui::Text("Position");
	ImGui::SameLine();
	ImGui::DragFloat3("##Relative Position", vPos);

	ImGui::Text("Scale   ");
	ImGui::SameLine();
	ImGui::DragFloat3("##Relative Scale", vScale);

	ImGui::Text("Rotation");
	ImGui::SameLine();
	ImGui::DragFloat3("##Relative Rotation", vRotation);

	GetTarget()->Transform()->SetRelativePos(vPos);
	GetTarget()->Transform()->SetRelativeScale(vScale);

	vRotation = (vRotation / 180.f) * XM_PI;
	GetTarget()->Transform()->SetRelativeRot(vRotation);

    

	return TRUE;
}
