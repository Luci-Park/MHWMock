#pragma once
#include "CComponent.h"
#include "CGameObject.h"

class CCanvas :
    public CComponent
{
private:
    vector<CGameObject*> _CavasObj;
public:
    virtual void tick() override;
    virtual void finaltick() override;

    void sortCanvasObj();
public:
    virtual void SaveToLevelFile(FILE* _File) {};
    virtual void LoadFromLevelFile(FILE* _FILE) {};

    CLONE(CCanvas);
public:
    CCanvas();
    ~CCanvas();
};

