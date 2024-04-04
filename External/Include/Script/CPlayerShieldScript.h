#pragma once
#include "pch.h"
#include "Engine\CScript.h"
#include "Engine\CGameObject.h"
#include "Engine\CAnimationStateMachine.h"
#include "Engine\CAnimator3D.h"

class CPlayerShieldScript
    : public CScript
{
public:
    enum class HandDir
    {
        Left,
        Right,
        Back,
        None,
    };
private:
    CAnimationStateMachine* _ASTM;
    CGameObject* m_pPlayer;
    CGameObject* m_pLeftBone;
    CGameObject* m_pRightBone;
    CGameObject* m_pBackBone;

    HandDir         m_eHandDir;
    bool            m_IsAttack;
public:
    virtual void begin();
    virtual void tick();

    virtual void OnCollisionEnter(CCollider3D* _Other) override;
    virtual void OnCollisionStay(CCollider3D* _Other) override;
    virtual void OnCollisionExit(CCollider3D* _Other) override;

    virtual void OnTriggerEnter(CCollider3D* _Other) override;
    virtual void OnTriggerExit(CCollider3D* _Other) override;

    virtual void OnAnimationBegin(IAnimationState* _pState) {}
    virtual void OnAnimationEndStart(IAnimationState* _pState) {}
    virtual void OnAnimationEndFinished(IAnimationState* _pState) {}

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
public:
    void ChangeParent(HandDir _HandDir);

public:
    void SetASTMParam(std::wstring paramID, AnimParamType type, AnimParamUnion param);
    AnimParamUnion GetASTMParam(std::wstring paramID);
    void IsAttack(bool isattack) { m_IsAttack = isattack; }
    void IsShieldAttack(bool isattack) { m_IsAttack = isattack; }
public:
    CPlayerShieldScript();
    ~CPlayerShieldScript();
    CLONE(CPlayerShieldScript);

};