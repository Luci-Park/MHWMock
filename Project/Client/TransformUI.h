#pragma once
#include "ComponentUI.h"

class CGameObject;

class TransformUI :
    public ComponentUI
{
public:
    virtual int render_update() override;

public:
    TransformUI();
    ~TransformUI();

    void Gizmo();
    void GizmoGui(ImGuiIO& io);

    DirectX::XMFLOAT4X4 change_mat(DirectX::XMMATRIX mat)
    {
        DirectX::XMFLOAT4X4 temp;
        DirectX::XMStoreFloat4x4(&temp, mat);

        return temp;
    }
private:
    float _DebugMeshScale;
    bool _useDebug;
};

