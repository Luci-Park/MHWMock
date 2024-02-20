#include "pch.h"
#include "CDamageScript.h"

#include <Engine\CEngine.h>
#include <Engine\CCamera.h>
#include <Engine\CFont.h>

CCamera* CDamageScript::m_UIcamera = nullptr;

CDamageScript::CDamageScript()
	: CScript((UINT)SCRIPT_TYPE::DAMAGESCRIPT)
{
	m_Owner = GetOwner();
	//m_Content.Content = L"";
	//m_Content.FontColor = FONT_RGBA(1.f, 0.f, 0.f, 1.f);
	//m_Content.FontSize = 25.f;
	//m_Content.FontPos = Vec2(m_Owner->Transform()->GetRelativePos().x, m_Owner->Transform()->GetRelativePos().y);
	m_Time = 0.f;
	m_on = false;
}

CDamageScript::~CDamageScript()
{
}

void CDamageScript::tick()
{
	TextInfo m_Content;

	//if (!m_on)
	//{
	//	m_Time = 0.f;
	//	m_Content.Content = L"";
	//	return;
	//}

	// 나중에 부딪힌 부분에서 damage 표시가 되도록 위치값을 수정해주세요!
	//m_Time += CTimeMgr::GetInst()->GetDeltaTime();
	m_Content.Content = L"testetstsets";
	m_Content.FontColor = FONT_RGBA(1.f, 0.f, 0.f, 1.f);
	m_Content.FontSize = 25.f;
	m_Content.FontPos = WorldPosToScreen(Vec3(0.f));

	CTextMgr::GetInst()->AddText(m_Content);
}

Vec2 CDamageScript::WorldPosToScreen(const Vec3 _pos)
{
	Viewport viewport = {};
	viewport.width = CEngine::GetInst()->GetWindowResolution().x;
	viewport.height = CEngine::GetInst()->GetWindowResolution().y;
	viewport.x = 0;
	viewport.y = 0;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	Vec3 screenPos = viewport.Project(_pos, m_UIcamera->GetProjMat(), m_UIcamera->GetViewMat(), Matrix::Identity);

	return Vec2(screenPos.x, screenPos.y);
}

