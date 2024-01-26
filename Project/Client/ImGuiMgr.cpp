#include "pch.h"
#include "ImGuiMgr.h" 
#include "ImGuizmo.h"

#include <Engine\CDevice.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CKeyMgr.h>
#include <Engine\CPathMgr.h>

#include <Engine\CGameObject.h>

#include "UI.h"
#include "ParamUI.h"
#include "Engine\CRenderMgr.h"
#include "Engine\CCamera.h"
#include "Engine\CTransform.h"
#include "OutlinerUI.h"

ImGuiMgr::ImGuiMgr()
    : m_hMainHwnd(nullptr)   
    , m_hObserver(nullptr)
{

}

ImGuiMgr::~ImGuiMgr()
{
    // ImGui Release
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // UI 삭제
    Safe_Del_Map(m_mapUI);
}


void ImGuiMgr::init(HWND _hWnd)
{
    m_hMainHwnd = _hWnd;

    // ImGui 초기화
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    //io.ConfigViewportsNoDefaultParent = true;
    //io.ConfigDockingAlwaysTabBar = true;
    //io.ConfigDockingTransparentPayload = true;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(m_hMainHwnd);
    ImGui_ImplDX11_Init(DEVICE, CONTEXT);



    // Tool 용 UI 생성
    CreateUI();

    // Content 폴더 감시
    wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
    m_hObserver = FindFirstChangeNotification(strContentPath.c_str(), true
        , FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME
        | FILE_ACTION_REMOVED | FILE_ACTION_ADDED);   
}

void ImGuiMgr::progress()
{
    begin();
    
    tick();
    finaltick();
    renderGizmo();

    render();

    // Content 폴더 변경 감시
    ObserveContent();
}



void ImGuiMgr::begin()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    float x = ImGui::GetMainViewport()->WorkPos.x;
    float y = ImGui::GetMainViewport()->WorkPos.y;
    float windowWidth = ImGui::GetMainViewport()->WorkSize.x;
    float windowHeight = ImGui::GetMainViewport()->WorkSize.y;

    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetRect(x, y, windowWidth, windowHeight);

    ParamUI::g_NextId = 0;

}

void ImGuiMgr::tick()
{
    for (const auto& pair : m_mapUI)
    {
        pair.second->tick();
    }    
}

void ImGuiMgr::finaltick()
{
    // Demo UI
    ImGui::ShowDemoWindow();

    // InspectorUI
    for (const auto& pair : m_mapUI)
    {
        if (pair.second->IsActive())
        {
            pair.second->finaltick();
        }        
    }

    if (KEY_TAP(KEY::ENTER))
        ImGui::SetWindowFocus(nullptr);


}

void ImGuiMgr::renderGizmo()
{

    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
    static ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;

    //Gizmo

    //GetTarget
    OutlinerUI* ui = (OutlinerUI*)FindUI("##Outliner");
    CGameObject* selectedObj = ui->GetSelectedObject();

    if (nullptr != selectedObj)
    {
        ImGui::Begin("Gizmo");
        //ImGuizmo::SetImGuiContext(ImGui::GetCurrentContext());
        ImGuizmo::AllowAxisFlip(false);
        ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

        //GetCamera Matrix
        CCamera* editorCamera = CRenderMgr::GetInst()->GetEditorCamera();
        XMMATRIX viewMat = editorCamera->GetViewMat();
        XMMATRIX projMat = editorCamera->GetProjMat();

        XMFLOAT4X4 v = change_mat(viewMat);
        XMFLOAT4X4 p = change_mat(projMat);

        v.m[0][0] = -v.m[0][0];
        v.m[1][0] = -v.m[1][0];
        v.m[2][0] = -v.m[2][0];
        //
        v.m[0][1] = -v.m[0][1];
        v.m[1][1] = -v.m[1][1];
        v.m[2][1] = -v.m[2][1];
        //
        v.m[0][2] = -v.m[0][2];
        v.m[1][2] = -v.m[1][2];
        v.m[2][2] = -v.m[2][2];

        //Get ojectTransformMatrix
        auto objTransform = selectedObj->GetComponent(COMPONENT_TYPE::TRANSFORM)->Transform();
        XMMATRIX objMat = objTransform->GetWorldMat();
        XMMATRIX objMatInv = objTransform->GetWorldInvMat();
        DirectX::XMFLOAT4X4 w = change_mat(objMat*objMatInv);

        ImGuiIO& io = ImGui::GetIO();

        ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "not over");
        ImGui::SameLine();
        ImGui::Text(ImGuizmo::IsOver(ImGuizmo::TRANSLATE) ? "Over translate gizmo" : "");
        ImGui::Text("X: %f Y: %f", io.MousePos.x, io.MousePos.y);

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

        ImGuizmo::Manipulate(*v.m, *p.m,mCurrentGizmoOperation, mCurrentGizmoMode, *w.m);

        if (ImGuizmo::IsOver())
        {
            ImGui::Text("Pos : X: %f Y: %f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
            int i = 0;
        }

        ImGui::End();
    }
}

void ImGuiMgr::render()
{
    // ImGui Rendering
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}


#include "InspectorUI.h"
#include "ContentUI.h"
#include "OutlinerUI.h"
#include "ListUI.h"
#include "MenuUI.h"

void ImGuiMgr::CreateUI()
{
    UI* pUI = nullptr;

    // InspectorUI
    pUI = new InspectorUI;
    pUI->SetActive(true);
    m_mapUI.insert(make_pair(pUI->GetID(), pUI));

    // ContentUI
    pUI = new ContentUI;
    pUI->SetActive(true);
    m_mapUI.insert(make_pair(pUI->GetID(), pUI));

    // Outliner
    pUI = new OutlinerUI;
    pUI->SetActive(true);
    m_mapUI.insert(make_pair(pUI->GetID(), pUI));

    // Menu
    pUI = new MenuUI;
    pUI->SetActive(true);
    m_mapUI.insert(make_pair(pUI->GetID(), pUI));


    // ListUI
    pUI = new ListUI;
    pUI->SetModal(true);
    pUI->SetActive(false);
    m_mapUI.insert(make_pair(pUI->GetID(), pUI));


    for (const auto& pair : m_mapUI)
    {
        pair.second->init();
    }
}

void ImGuiMgr::ObserveContent()
{
    DWORD dwWaitStatus = WaitForSingleObject(m_hObserver, 0);

    if (dwWaitStatus == WAIT_OBJECT_0)
    {
        // content 폴더에 변경점이 생겼다.
        ContentUI* UI = (ContentUI*)FindUI("##Content");
        UI->Reload();

        FindNextChangeNotification(m_hObserver);        
    }
}


UI* ImGuiMgr::FindUI(const string& _UIName)
{
    map<string, UI*>::iterator iter = m_mapUI.find(_UIName);

    if(iter == m_mapUI.end())
        return nullptr;

    return iter->second;
}