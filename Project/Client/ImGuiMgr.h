#pragma once
#include <Engine\CSingleton.h>

#include "ImGui\imgui.h"
#include "ImGui/imgui_stdlib.h"
#include "ImGui\imgui_impl_dx11.h"
#include "ImGui\imgui_impl_win32.h"


// ========
// Delegate
// ========
class UI;

typedef void (UI::* UI_DELEGATE)(void);
typedef void (UI::* UI_DELEGATE_1)(DWORD_PTR);
typedef void (UI::* UI_DELEGATE_2)(DWORD_PTR, DWORD_PTR);

class ImGuiMgr :
    public CSingleton<ImGuiMgr>
{
    SINGLE(ImGuiMgr);
private:
    HWND                m_hMainHwnd;
    map<string, UI*>    m_mapUI;

    HANDLE              m_hObserver;


public:
    void init(HWND _hWnd);
    void progress();

public:
    UI* FindUI(const string& _UIName);
    HWND GetMainHwnd() { return m_hMainHwnd; }

private:
    void CreateUI();
    void ObserveContent();

    void begin();
    void tick();
    void finaltick();
    void renderGizmo();
    void render();

    DirectX::XMFLOAT4X4 change_mat(DirectX::XMMATRIX mat)
    {
        DirectX::XMFLOAT4X4 temp;
        DirectX::XMStoreFloat4x4(&temp, mat);

        return temp;
    }

    float* matrix_to_float_array(DirectX::XMMATRIX mat)
    {
        DirectX::XMFLOAT4X4* temp = new DirectX::XMFLOAT4X4();
        DirectX::XMStoreFloat4x4(temp, mat);

        float m16[16];

        m16[0] = temp->_11;
        m16[1] = temp->_12;
        m16[2] = temp->_13;
        m16[3] = temp->_14;
        m16[4] = temp->_21;
        m16[5] = temp->_22;
        m16[6] = temp->_23;
        m16[7] = temp->_24;
        m16[8] = temp->_31;
        m16[9] = temp->_32;
        m16[10] = temp->_33;
        m16[11] = temp->_34;
        m16[12] = temp->_41;
        m16[13] = temp->_42;
        m16[14] = temp->_43;
        m16[15] = temp->_44;

        return m16;
    }


};

