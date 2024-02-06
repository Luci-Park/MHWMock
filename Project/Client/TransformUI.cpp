#include "pch.h"
#include "TransformUI.h"
#include "OutlinerUI.h"
#include <Engine/CRenderMgr.h>
#include <Engine\CCamera.h>

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>

static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
static ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
static ImGuiWindowFlags gizmoWindowFlags = 0;
bool useWindow = true;

TransformUI::TransformUI()
	: ComponentUI("##Transform", COMPONENT_TYPE::TRANSFORM)	
    , _DebugMeshScale(10.f)
    , _useDebug(false)
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
        ImGuizmo::AllowAxisFlip(false);
        ImGui::Begin("Gizmo");
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

        //Set Gizmo Viewport
        //1280 * 768
        ImGuiIO& io = ImGui::GetIO();
        float x = ImGui::GetMainViewport()->WorkPos.x;
        float y = ImGui::GetMainViewport()->WorkPos.y;
        float windowWidth = ImGui::GetMainViewport()->WorkSize.x;
        float windowHeight = ImGui::GetMainViewport()->WorkSize.y;

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

        //Debug Cube
        //Draw Cude at Objcet position
        if (_useDebug)
        {
            //Edit Scale
            XMFLOAT4X4 temp = objMat;
            temp.m[0][0] *= _DebugMeshScale;
            temp.m[1][1] *= _DebugMeshScale;
            temp.m[2][2] *= _DebugMeshScale;
            
            //Draw Cude
            ImGuizmo::DrawCubes(*viewMat.m, *projMat.m, *temp.m, 1);
        }

        //Edit Object Transform
        if (ImGuizmo::IsUsing())
        {
            Vec3 pos, scale;
            Quaternion rot;
            Matrix matObjMat = objMat;
            matObjMat.Decompose(scale, rot, pos);
            //float scale[3];
            //float rotation[3];
            //float translation[3];
            //
            //ImGuizmo::DecomposeMatrixToComponents(*objMat.m, translation, rotation, scale);
            //
            ////for (int i = 0; i < 3; i++)
            ////{
            ////    rotation[i] *= XM_PI / 180.0f;
            ////}
            selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform()->SetRelativePos(pos);
            selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform()->SetRelativeRot(rot);
            selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform()->SetRelativeScale(scale);
        }

        GizmoGui(io);
        ImGui::End();
    }
}

void TransformUI::GizmoGui(ImGuiIO& io)
{
    //Gizmo Render Mode
    if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
        mCurrentGizmoMode = ImGuizmo::LOCAL;
    ImGui::SameLine();
    if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
        mCurrentGizmoMode = ImGuizmo::WORLD;

    //Gizmo Operator
    if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
        mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
        mCurrentGizmoOperation = ImGuizmo::ROTATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
        mCurrentGizmoOperation = ImGuizmo::SCALE;

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

    //Debug Mesh
    ImGui::Checkbox("Debug Mesh", &_useDebug);
    if (_useDebug)
        ImGui::SliderFloat("Debug Mesh Scale",&_DebugMeshScale,1.f,10000.f);

    //Debug Mouse pos
    ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "not over");
    ImGui::Text("Mouse Pos X: %f Y: %f", io.MousePos.x, io.MousePos.y);
}

int TransformUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;

    Gizmo();

	Vec3 vPos = GetTarget()->Transform()->GetRelativePos();
	Vec3 vScale = GetTarget()->Transform()->GetRelativeScale();
    Vec3 vRotation = GetTarget()->Transform()->GetRelativeEulerRot();

	ImGui::Text("Position");
	ImGui::SameLine();
	ImGui::DragFloat3("##Relative Position", vPos);

	ImGui::Text("Rotation");
	ImGui::SameLine();
	ImGui::DragFloat3("##Relative Rotation", vRotation);

    ImGui::Text("Scale   ");
    ImGui::SameLine();
    ImGui::DragFloat3("##Relative Scale", vScale);

    GetTarget()->Transform()->SetRelativePos(vPos);
	GetTarget()->Transform()->SetRelativeScale(vScale);

	GetTarget()->Transform()->SetRelativeRot(vRotation);

	return TRUE;
}
