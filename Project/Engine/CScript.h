#pragma once
#include "CComponent.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CGameObject.h"
#include "components.h"


enum class SCRIPT_PARAM
{
    INT,
    FLOAT,
    VEC2,
    VEC4,
    TEXTURE,
    GAMEOBJECT,
};

struct tScriptParam
{
    SCRIPT_PARAM    eParam;
    void*           pData;    
    string          strDesc;
};

class CCollider3D;

class CScript :
    public CComponent
{
private:  
    UINT                    m_iScriptType;
    vector<tScriptParam>    m_vecParam;
    bool                    m_bGameObjectParamSet;
    vector<list<int>>       m_vecGameObjParams;
    vector<CGameObject**>   m_vecParamObjs;

public:
    void Destroy() { DestroyObject(GetOwner()); }
    void SetLifeSpan(float _Time) { GetOwner()->SetLifeSpan(_Time); }
    UINT GetScriptType() { return m_iScriptType; }
    const vector<tScriptParam>& GetScriptParam() { return m_vecParam; }

public:
    virtual void finaltick() final;
    virtual void OnCollisionEnter(CCollider3D* _Other) {}
    virtual void OnCollisionStay(CCollider3D* _Other) {}
    virtual void OnCollisionExit(CCollider3D* _Other) {}


    virtual void OnTriggerEnter(CCollider3D* _Other) {}
    virtual void OnTriggerExit(CCollider3D* _Other) {}

public:
    virtual void SaveToLevelFile(FILE* _File) override {}
    virtual void LoadFromLevelFile(FILE* _FILE) override {}

protected:
    void AddScriptParam(SCRIPT_PARAM eParam, void* _pData, const string& _Desc);
    void SaveGameObjectParam(CGameObject* _Obj, FILE* _File);
    void LoadGameObjectParam(int _vecIdx, FILE* _File);

private:
    void FindGameObject();

public:
    CScript(UINT _iScriptType);
    ~CScript();
};

