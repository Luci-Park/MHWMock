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
	Vec3 TransformCoord(const Vector3& vector, const Matrix& matrix);
	Vec3 GetCameraCenterFromWorldPos(const Vec3& worldPos);


	virtual void tick() override;

private:
	CGameObject* m_Owner;
	CGameObject* m_Target;
	//TextInfo m_Content;
	float m_Time;
	static CCamera* m_UIcamera;

	Vec3 m_FirstPos;

	float m_255 = 255.f;
	bool m_on;
};

