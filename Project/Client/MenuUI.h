#pragma once
#include "UI.h"


class MenuUI :
    public UI
{
private:
    string m_strMatName;

public:
    virtual void finaltick() override;
    virtual int render_update() override;


private:
    void CreateEmptyObject();
    void CreateEmptyMaterial(string strName);
    void SaveObject();
    void LoadObject();
    void AddComponent(COMPONENT_TYPE _type);
    void AddScript(const wstring& _strScriptName);

    vector<wstring> GetLevels();
public:
    MenuUI();
    ~MenuUI();
};

