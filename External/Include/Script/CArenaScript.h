#pragma once
#include <Engine\CScript.h>

class CArenaScript :
    public CScript
{
private:
    bool                m_bComplete;
    float                m_fTime;

    CGameObject*   m_pCompleteObj;


public:
    void CompleteQuest();

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CArenaScript);
public:

    CArenaScript();
    ~CArenaScript();
};

