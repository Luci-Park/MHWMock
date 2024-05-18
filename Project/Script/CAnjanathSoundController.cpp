#include "pch.h"
#include "CAnjanathSoundController.h"


CAnjanathSoundController::CAnjanathSoundController()
	:CScript(SCRIPT_TYPE::ANJANATHSOUNDCONTROLLER)
{
}

CAnjanathSoundController::~CAnjanathSoundController()
{
}

void CAnjanathSoundController::Roar(Ptr<CAnimationClip> _clip, double _percent)
{
	if (_clip->GetName() != L"Animation 001.002") return;
	if ((int)_percent == 0 || ((int)_percent == 126))
		CResMgr::GetInst()->FindRes<CSound>(L"sound\\030(Roar).mp3")->Play(1, 0.2, true);
}

void CAnjanathSoundController::update()
{
	double percent;
	Ptr<CAnimationClip> currClip = Animator3D()->GetCurrentAnimation(percent);
	if (currClip == nullptr) return;
	Roar(currClip, percent);
}
