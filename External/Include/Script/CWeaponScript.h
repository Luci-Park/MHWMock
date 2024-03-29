#pragma once
#include "pch.h"
#include "Engine\CScript.h"
#include "Engine\CGameObject.h"
#include "Engine\CAnimationStateMachine.h"
#include "Engine\CAnimator3D.h"

class CWeaponScript
	: public CScript
{
protected:
    CAnimationStateMachine* _ASTM;
    CGameObject* _Player;
    CGameObject* _MainBone;
    CGameObject* _SubBone;
public:
    virtual void begin();
    virtual void tick() override {}

    virtual void OnCollisionEnter(CCollider3D* _Other) {}
    virtual void OnCollisionStay(CCollider3D* _Other) {}
    virtual void OnCollisionExit(CCollider3D* _Other) {}

    virtual void OnTriggerEnter(CCollider3D* _Other) {}
    virtual void OnTriggerExit(CCollider3D* _Other) {}

    virtual void OnAnimationBegin(IAnimationState* _pState) {}
    virtual void OnAnimationEndStart(IAnimationState* _pState) {}
    virtual void OnAnimationEndFinished(IAnimationState* _pState) {}

    virtual void SaveToLevelFile(FILE* _File) override {}
    virtual void LoadFromLevelFile(FILE* _FILE) override {}
public:
	CWeaponScript();
	virtual ~CWeaponScript();
	CLONE(CWeaponScript);
public:
    void SetASTMParam(std::wstring paramID,AnimParamType type, AnimParamUnion param);
    AnimParamUnion GetASTMParam(std::wstring paramID);
    void SetMainBone() { GetOwner()->SetParent(_MainBone); }
    void SetSubBone() { GetOwner()->SetParent(_SubBone); }
};