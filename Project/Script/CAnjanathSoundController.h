#pragma once
#include <Engine/CScript.h>
class CAnjanathSoundController :
	public CScript
{
private:
	void Roar(Ptr<CAnimationClip> _clip, double _percent);
public:
	virtual void update() override;
public:
	CLONE(CAnjanathSoundController);
	CAnjanathSoundController();
	~CAnjanathSoundController();
};

