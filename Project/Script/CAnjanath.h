#pragma once
#include <Engine/CScript.h>
class CAnjanath :
	public CScript
{
private:
	CGameObject* m_pPlayer;
	float m_fRotateSpeed;
	float m_fDistance;
	float m_fAngle;
private:
	void RotateTowardsPlayer();
public:
	virtual void tick() override;
	
	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _FILE) override;
public:
	CLONE(CAnjanath)
	CAnjanath();
	~CAnjanath();
};

