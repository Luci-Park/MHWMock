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
    //static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
    //static ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;

    CGameObject* selectedObj = GetTarget();
    if (nullptr != selectedObj)
    {
        ImGui::Begin("Gizmo");
        ImGuizmo::AllowAxisFlip(false);

        //if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
        //    mCurrentGizmoMode = ImGuizmo::LOCAL;
        //ImGui::SameLine();
        //if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
        //    mCurrentGizmoMode = ImGuizmo::WORLD;

        //if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
        //    mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
        //ImGui::SameLine();
        //if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
        //    mCurrentGizmoOperation = ImGuizmo::ROTATE;
        //ImGui::SameLine();
        //if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
        //    mCurrentGizmoOperation = ImGuizmo::SCALE;

        //ImGui::GetBackgroundDrawList();
        ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
        //ImGuizmo::SetDrawlist(ImGui::GetForegroundDrawList());
        //ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());

        //Set Gizmo Viewport
        //1280 * 768

        //float x = ImGui::GetWindowPos().x;
        //float y = ImGui::GetWindowPos().y;
        //float windowWidth = ImGui::GetWindowSize().x;
        //float windowHeight = ImGui::GetWindowSize().y;

        //ImGuiIO& io = ImGui::GetIO();
        float viewManipulateRight = ImGui::GetWindowSize().x;
        float viewManipulateTop = 0;
        viewManipulateRight = ImGui::GetWindowPos().x + ImGui::GetWindowSize().x;
        viewManipulateTop = ImGui::GetWindowPos().y;

        

        CCamera* editorCamera = CRenderMgr::GetInst()->GetEditorCamera();

        XMMATRIX viewMat = editorCamera->GetViewMat();
        XMMATRIX projMat = editorCamera->GetProjMat();

        XMFLOAT4X4 v = change_mat(viewMat);
        XMFLOAT4X4 p = change_mat(projMat);

        //Get ojectTransformMatrix
        auto objTransform = selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform();
        XMMATRIX objMat = objTransform->GetWorldMat();
        XMMATRIX objInvMat = objTransform->GetWorldInvMat();
        DirectX::XMFLOAT4X4 w = change_mat((objMat*objInvMat));

        XMMATRIX viewInv = editorCamera->GetViewInvMat();
        XMFLOAT4X4 iv = change_mat(viewInv);

        float pos[3] = { objTransform->GetRelativePos().x, objTransform->GetRelativePos().y, objTransform->GetRelativePos().z };
        float rot[3] = { objTransform->GetRelativeRot().x, objTransform->GetRelativeRot().y,objTransform->GetRelativeRot().z};
        float scl[3] = { objTransform->GetRelativeScale().x, objTransform->GetRelativeScale().y, objTransform->GetRelativeScale().z };

        ImGuizmo::RecomposeMatrixFromComponents(pos, rot, scl, *w.m);

        //Render Gizmo
        //ImGuizmo::Manipulate(*v.m, *p.m, mCurrentGizmoOperation, mCurrentGizmoMode, *w.m);
        ImGuizmo::ViewManipulate(*v.m, 0.5f, ImVec2(viewManipulateRight, viewManipulateTop), ImVec2(128, 128), 0x10101010);
        if(ImGuizmo::IsOver())
        {
            int a = 0;
        }

        if (ImGuizmo::IsUsing())
        {

            ImGuizmo::DecomposeMatrixToComponents(*w.m, pos, rot, scl);
            objTransform->SetWorldMat(w);
        }

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "not over");
        ImGui::SameLine();
        ImGui::Text(ImGuizmo::IsOver(ImGuizmo::TRANSLATE) ? "Over translate gizmo" : "");
        ImGui::Text("X: %f Y: %f", io.MousePos.x, io.MousePos.y);

        ImGui::End();
    }
}

int TransformUI::render_update()
{

	if (FALSE == ComponentUI::render_update())
		return FALSE;

    //Gizmo();

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
