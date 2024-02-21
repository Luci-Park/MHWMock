#pragma once
#include "CEntity.h"

class CRes :
    public CEntity
{
private:
    const RES_TYPE  m_Type;
    int             m_iRefCount;

    wstring         m_strRelativePath;

    bool            m_bEngine;

protected:
    void SetKey(const wstring& _strKey) { SetRelativePath(_strKey); }
    void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

private:
    void AddRef() { ++m_iRefCount; }
    void Release();


    virtual void UpdateData() {};


public:
    virtual int Save(const wstring& _strFilePath) = 0;
    virtual int Load(const wstring& _strFilePath) = 0;

    virtual CRes* Clone() { return nullptr; assert(nullptr); }

public:
    const wstring& GetKey() { return m_strRelativePath; }
    const wstring& GetRelativePath() { return m_strRelativePath; }
    RES_TYPE GetType() { return m_Type; }
    bool IsEngineRes() { return m_bEngine; }

public:
    CRes(RES_TYPE _type, bool _bEngine = false);
    CRes(const CRes& _Other);
    virtual ~CRes();

    friend class CResMgr;

    template<typename T>
    friend class Ptr;
};

