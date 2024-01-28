#include "pch.h"
#include "TransformUI.h"
#include "OutlinerUI.h"
#include "Engine\CRenderMgr.h"
#include "Engine\CCamera.h"

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>

static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
static ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
static ImGuiWindowFlags gizmoWindowFlags = 0;
bool useWindow = true;

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
        ImGui::Begin("Gizmo");

        //Set Gizmo Viewport
        //1280 * 768
        ImGuiIO& io = ImGui::GetIO();
        float x = ImGui::GetMainViewport()->WorkPos.x;
        float y = ImGui::GetMainViewport()->WorkPos.y;
        float windowWidth = ImGui::GetMainViewport()->WorkSize.x;
        float windowHeight = ImGui::GetMainViewport()->WorkSize.y;
        
        ImGuizmo::AllowAxisFlip(false);
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImGuizmo::SetRect(x, y, windowWidth, windowHeight);

        //Get Camera View Projection Matrix
        CCamera* editorCamera = CRenderMgr::GetInst()->GetEditorCamera();
        XMFLOAT4X4 viewMat = change_mat(editorCamera->GetViewMat());
        XMFLOAT4X4 projMat = change_mat(editorCamera->GetProjMat());

        //Get OjectTransform Matrix
        auto objTransform = selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform();
        XMFLOAT4X4 objMat = change_mat(objTransform->GetWorldMat());

        //Render Gizmo
        ImGuizmo::Manipulate(*viewMat.m, *projMat.m, mCurrentGizmoOperation, mCurrentGizmoMode, *objMat.m);

        if (ImGuizmo::IsUsing())
        {
            float scale[3];
            float rotation[3];
            float translation[3];

            ImGuizmo::DecomposeMatrixToComponents(*objMat.m, translation, rotation, scale);

            for (int i = 0; i < 3; i++)
            {
                rotation[i] *= XM_PI / 180.0f;
            }
            selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform()->SetRelativePos(Vec3(translation[0], translation[1], translation[2]));
            selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform()->SetRelativeRot(Vec3(rotation[0], rotation[1], rotation[2]));
            selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform()->SetRelativeScale(Vec3(scale[0], scale[1], scale[2]));
        }

        GizmoGui(io);
        ImGui::End();
    }
}

void TransformUI::GizmoGui(ImGuiIO& io)
{
    if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
        mCurrentGizmoMode = ImGuizmo::LOCAL;
    ImGui::SameLine();
    if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
        mCurrentGizmoMode = ImGuizmo::WORLD;

    if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
        mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
        mCurrentGizmoOperation = ImGuizmo::ROTATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
        mCurrentGizmoOperation = ImGuizmo::SCALE;

    ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "not over");

    if (ImGuizmo::IsUsing())
    {
        ImGui::SameLine();
        switch (mCurrentGizmoOperation)
        {
        case ImGuizmo::TRANSLATE:
            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::TRANSLATE) ? "Using translate gizmo" : "");
            break;
        case ImGuizmo::ROTATE:
            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::ROTATE) ? "Using Rotate gizmo" : "");
            break;
        case ImGuizmo::SCALE:
            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::SCALE) ? "Using Scale gizmo" : "");
            break;
        default:
            break;
        }
    }
    ImGui::Text("Mouse Pos X: %f Y: %f", io.MousePos.x, io.MousePos.y);
}

int TransformUI::render_update()
{

	if (FALSE == ComponentUI::render_update())
		return FALSE;

    Gizmo();

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
