#pragma once
#include <Engine\CScript.h>

class CDamageScript
	: public CScript
{
public:
	CDamageScript();
	~CDamageScript();

	CLONE(CDamageScript);

	void SetUIcamera(CCamera* _UI) { m_UIcamera = _UI; }
	Vec2 WorldPosToScreen(const Vec3 _pos);
	virtual void tick() override;

private:
	CGameObject* m_Owner;
	CGameObject* m_Target;
	//TextInfo m_Content;
	float m_Time;
	static CCamera* m_UIcamera;

	bool m_on;
};

