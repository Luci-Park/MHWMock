#pragma once
#include "Engine\CTransform.h"
#include "Engine\CScript.h"
#include "Engine\CAnimationStateMachine.h"

class CSwordScript :
    public CScript
{
private:
    enum class Mode
    {
        Knife,
        Axe,
        None,
    };
    Mode mode;
    CAnimationStateMachine* _ASTM;
    CGameObject*    _Player;
    CGameObject*    _MainBone;
    CGameObject*    _SubBone;
    CGameObject*    _LightingParticle;
    bool            _IsAttack;
public:
    CSwordScript();
    ~CSwordScript();
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void OnCollisionEnter(CCollider3D* _Other);
    virtual void OnCollisionStay(CCollider3D* _Other);
    virtual void OnCollisionExit(CCollider3D* _Other);

    virtual void OnTriggerEnter(CCollider3D* _Other);
    virtual void OnTriggerExit(CCollider3D* _Other);

    virtual void OnAnimationBegin(IAnimationState* _pState);
    virtual void OnAnimationEndStart(IAnimationState* _pState);
    virtual void OnAnimationEndFinished(IAnimationState* _pState);

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
public:
    void SetASTMParam(std::wstring paramID, AnimParamType type, AnimParamUnion param);
    AnimParamUnion GetASTMParam(std::wstring paramID);
    void SetMainBone(int type);
    void SetSubBone();
    void IsAttack(bool isattack) { _IsAttack = isattack; }

    void LightingEffect();
public:
    CLONE(CSwordScript);
};

