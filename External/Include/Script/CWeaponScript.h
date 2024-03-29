#pragma once
#include "pch.h"
#include "Engine\CScript.h"

class CWeaponScript
	: public CScript
{
public:
    virtual void begin() {}
    virtual void tick() {}

    virtual void OnCollisionEnter(CCollider3D* _Other) {}
    virtual void OnCollisionStay(CCollider3D* _Other) {}
    virtual void OnCollisionExit(CCollider3D* _Other) {}

    virtual void OnTriggerEnter(CCollider3D* _Other) {}
    virtual void OnTriggerExit(CCollider3D* _Other) {}

    virtual void OnAnimationBegin(IAnimationState* _pState) {}
    virtual void OnAnimationEndStart(IAnimationState* _pState) {}
    virtual void OnAnimationEndFinished(IAnimationState* _pState) {}
public:
	CWeaponScript();
	~CWeaponScript();
public:
	CLONE(CWeaponScript);
};