#include "pch.h"
#include "MenuUI.h"

#include "CLevelSaveLoad.h"

#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>
#include <Engine\CScript.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLayer.h>
#include <Script\CScriptMgr.h>



#include "ImGuiMgr.h"
#include "OutlinerUI.h"
#include "InspectorUI.h"
#include "ContentUI.h"
#include "CLevelSaveLoad.h"
#include "ListUI.h"
#include "test.cpp"



MenuUI::MenuUI()
	: UI("##Menu")
{
	SetName("Menu");
}

MenuUI::~MenuUI()
{
}

void MenuUI::finaltick()
{
    if (!IsActive())
        return;

    render_update();
}

int MenuUI::render_update()
{
    string popupflag = "";
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save Level"))
            {
                CLevel* pLoadedLevel = CLevelMgr::GetInst()->GetCurLevel();

                wstring strPath = L"level\\" + pLoadedLevel->GetName() + L".lv";
                assert(CLevelSaveLoad::SaveLevel(strPath, pLoadedLevel) == S_OK);
            }

            if (ImGui::BeginMenu("Load Level"))
            {
                auto vecLevels = GetLevels();
                for (int i = 0; i < vecLevels.size(); i++)
                {
                    string strNarrow(vecLevels[i].begin(), vecLevels[i].end());
                    if (ImGui::MenuItem(strNarrow.c_str()))
                    {
                        wstring filename = L"level\\" + vecLevels[i] + L".lv";
                        // Level �ҷ�����
                        CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(filename);

                        tEvent evn = {};
                        evn.Type = EVENT_TYPE::LEVEL_CHANGE;
                        evn.wParam = (DWORD_PTR)pLoadedLevel;
                        
                        CEventMgr::GetInst()->AddEvent(evn);
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Create Level"))
            {
                //luci TODO: Create Level with name input
                CLevel* pNewLevel = new CLevel;
                wstring strLevelName = L"New Level" + to_wstring(pNewLevel->GetID());
                pNewLevel->SetName(strLevelName);

                wstring strPath = L"level\\" + pNewLevel->GetName() + L".lv";
                assert(CLevelSaveLoad::SaveLevel(strPath, pNewLevel) == S_OK);

                tEvent evn = {};
                evn.Type = EVENT_TYPE::LEVEL_CHANGE;
                evn.wParam = (DWORD_PTR)pNewLevel;

                CEventMgr::GetInst()->AddEvent(evn);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject"))
        {
            // ���� ������ ���ӿ�����Ʈ ����
            if (ImGui::MenuItem("Create Empty Object"))
            {
                CreateEmptyObject();
            }
            ImGui::Separator();

            if (ImGui::MenuItem("Save Object"))
            {
                SaveObject();
            }
            ImGui::Separator();

            if (ImGui::MenuItem("Load Object"))
            {
                LoadObject();
            }
            ImGui::Separator();

            if (ImGui::MenuItem("Delete Object"))
            {
                DeleteObject();
            }
            ImGui::Separator();

            
            if (ImGui::BeginMenu("Add Component"))
            {
                for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
                {
                    if (ImGui::MenuItem(ToString((COMPONENT_TYPE)i)))
                    {
                        AddComponent(COMPONENT_TYPE(i));
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::BeginMenu("Add Script"))
            {
                vector<wstring> vecScripts;
                CScriptMgr::GetScriptInfo(vecScripts);
                
                for (size_t i = 0; i < vecScripts.size(); ++i)
                {
                    string strScriptName = string(vecScripts[i].begin(), vecScripts[i].end());
                    if (ImGui::MenuItem(strScriptName.c_str()))
                    {
                        AddScript(vecScripts[i]);
                    }
                }
                
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Level"))
        {
            CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
            bool PlayEnable = true;
            bool PauseEnable = true;
            bool StopEnable = true;

            if (CurLevel->GetState() == LEVEL_STATE::PLAY)
            {
                PlayEnable = false;
                PauseEnable = true;
                StopEnable = true;
            }
            else if (CurLevel->GetState() == LEVEL_STATE::PAUSE)
            {
                PlayEnable = true;
                PauseEnable = false;
                StopEnable = true;
            }
            else if (CurLevel->GetState() == LEVEL_STATE::STOP)
            {
                PlayEnable = true;
                PauseEnable = false;
                StopEnable = false;
            }
                

            if (ImGui::MenuItem("Play", nullptr, nullptr, PlayEnable))
            {                
                CLevelSaveLoad::SaveLevel(L"level\\Temp.lv", CurLevel);
                CurLevel->ChangeState(LEVEL_STATE::PLAY);
            }
            else if (ImGui::MenuItem("Pause", nullptr, nullptr, PauseEnable))
            {
                CurLevel->ChangeState(LEVEL_STATE::PAUSE);
            }
            else if (ImGui::MenuItem("Stop", nullptr, nullptr, StopEnable))
            {
                CurLevel->ChangeState(LEVEL_STATE::STOP);
                CLevel* pNewLevel = CLevelSaveLoad::LoadLevel(L"level\\Temp.lv");
             
                tEvent evn = {};
                evn.Type = EVENT_TYPE::LEVEL_CHANGE;
                evn.wParam = DWORD_PTR(pNewLevel);
                CEventMgr::GetInst()->AddEvent(evn);

                // InspectorUI
                InspectorUI* Inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
                Inspector->SetTargetObject(nullptr);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Resource"))
        {
            if (ImGui::MenuItem("Create Empty Material"))
            {
                popupflag = "Mat";
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    if(popupflag == "Mat") ImGui::OpenPopup("Material Name");
    if (ImGui::BeginPopup("Material Name"))
    {
        ImGui::Text("Enter Material Name:");
        ImGui::InputText("##MaterialName", &m_strMatName);
        if (ImGui::Button("Create"))
        {
            CreateEmptyMaterial(m_strMatName);
            m_strMatName = "";
            ImGui::CloseCurrentPopup(); // Close the popup after creating the material
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
        {
            m_strMatName = "";
            ImGui::CloseCurrentPopup(); // Close the popup without creating the material
        }

        ImGui::EndPopup();
    }

	return 0;
}

void MenuUI::CreateEmptyObject()
{
    CGameObject* pNewObject = new CGameObject;
    pNewObject->AddComponent(new CTransform);
    pNewObject->SetName(L"New Object");
    SpawnGameObject(pNewObject, Vec3(0.f, 0.f, 0.f), ToWString((LAYER_TYPE)0));

    // Outliner �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");

    // �����߰��� ������Ʈ�� �����ͷ� �ϴ� ��尡 �߰��Ǹ�, ���û��·� �ΰ� �Ѵ�.
    outliner->SetSelectedNodeData(DWORD_PTR(pNewObject));    
}

void MenuUI::SaveObject()
{
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    CGameObject* pSelectedObject = outliner->GetSelectedObject();
    if (!pSelectedObject)
        return;
    FILE* saveFile;
    wstring strPath = CPathMgr::GetInst()->GetContentPath();
    wstring filename = L"obj\\" + pSelectedObject->GetName() + L".cgobj";
    strPath += filename;
    _wfopen_s(&saveFile, strPath.c_str(), L"ab");
    assert(CLevelSaveLoad::SaveGameObject(pSelectedObject, saveFile) == S_OK);
    fclose(saveFile);
}

void MenuUI::LoadObject()
{
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    ContentUI* content = (ContentUI*)ImGuiMgr::GetInst()->FindUI("##Content");
    wstring strPath = CPathMgr::GetInst()->GetContentPath();
    FILE* loadFile = BrowserOpen();
    CGameObject* pSelectedObject = CLevelSaveLoad::LoadGameObject(loadFile);
    tEvent evn;
    evn.wParam = (DWORD_PTR)pSelectedObject;
    evn.lParam = 0;
    evn.Type = EVENT_TYPE::CREATE_OBJECT;
    CEventMgr::GetInst()->AddEvent(evn);
    content->Reload();
}

void MenuUI::DeleteObject()
{
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    CGameObject* pSelectedObject = outliner->GetSelectedObject();
    DestroyObject(pSelectedObject);
}

void MenuUI::CreateEmptyMaterial(string strName)
{
    Ptr<CMaterial> pNewMtrl = new CMaterial;
    wstring wstrName(strName.begin(), strName.end());
    pNewMtrl->SetName(wstrName);
    wstring strPath = L"material\\" + pNewMtrl->GetName() + L".mtrl";
    CResMgr::GetInst()->AddRes<CMaterial>(strPath, pNewMtrl);
    pNewMtrl->Save(strPath);

}

void MenuUI::AddComponent(COMPONENT_TYPE _type)
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

    // ���õ� ������Ʈ�� �����ͼ� ComponentType �� �´� ������Ʈ�� �����ؼ� �߰��Ѵ�.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    switch (_type)
    {
    case COMPONENT_TYPE::TRANSFORM:
        pSelectedObject->AddComponent(new CTransform);
        break;
    case COMPONENT_TYPE::COLLIDER2D:
        pSelectedObject->AddComponent(new CCollider2D);
        break;
    case COMPONENT_TYPE::COLLIDER3D:
        pSelectedObject->AddComponent(new CCollider3D);
        break;
    case COMPONENT_TYPE::ANIMATOR2D:
        pSelectedObject->AddComponent(new CAnimator2D);
        break;
    case COMPONENT_TYPE::ANIMATOR3D:
        //pSelectedObject->AddComponent(new CAnimator3D);
        break;
    case COMPONENT_TYPE::LIGHT2D:
        pSelectedObject->AddComponent(new CLight2D);
        break;
    case COMPONENT_TYPE::LIGHT3D:
        pSelectedObject->AddComponent(new CLight3D);
        break;
    case COMPONENT_TYPE::CAMERA:
        pSelectedObject->AddComponent(new CCamera);
        break;
    case COMPONENT_TYPE::MESHRENDER:
        pSelectedObject->AddComponent(new CMeshRender);
        break;
    case COMPONENT_TYPE::PARTICLESYSTEM:
        pSelectedObject->AddComponent(new CParticleSystem);
        break;
    case COMPONENT_TYPE::TILEMAP:
        pSelectedObject->AddComponent(new CTileMap);
        break;
    case COMPONENT_TYPE::LANDSCAPE:
        pSelectedObject->AddComponent(new CLandScape);
        break;
    case COMPONENT_TYPE::DECAL:
        //pSelectedObject->AddComponent(new CDecal);
        break;            
    }

    // Inspector �� ���Ӱ� �߰��� ������Ʈ�� �˸��� ���ؼ� Ÿ���� �ٽ� �˷��ش�.
    inspector->SetTargetObject(pSelectedObject);

}

void MenuUI::AddScript(const wstring& _strScriptName)
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

    // ���õ� ������Ʈ�� �����ͼ� ComponentType �� �´� ������Ʈ�� �����ؼ� �߰��Ѵ�.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    CScript* pScript = CScriptMgr::GetScript(_strScriptName);

    pSelectedObject->AddComponent(pScript);

    inspector->SetTargetObject(pSelectedObject);
}

std::vector<std::wstring> MenuUI::GetLevels()
{
    std::vector<std::wstring> levels;
    wstring filename = CPathMgr::GetInst()->GetContentPath();
    filename += L"level\\";
    try {
        path contentPath = filename;

        for (const auto& entry : directory_iterator(contentPath)) {
            if (is_regular_file(entry) && entry.path().extension() == L".lv") {
                levels.push_back(entry.path().stem().wstring());
            }
        }
    }
    catch (const std::exception& e) {
        // Handle exceptions (e.g., display an error message, log the error)
        // For example: std::cerr << "Error: " << e.what() << std::endl;
    }

    return levels;
}

