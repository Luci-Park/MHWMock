#include "pch.h"
#include "CDamageScript.h"

#include <Engine\CEngine.h>
#include <Engine\CCamera.h>
#include <Engine\CFont.h>

CCamera* CDamageScript::m_UIcamera = nullptr;

CDamageScript::CDamageScript()
	: CScript((UINT)SCRIPT_TYPE::DAMAGESCRIPT)
	, m_Target(nullptr)
{
	m_FirstPos = Vec3(0.f, 0.f, 10.f);
	m_on = true;
	m_255 = 255.f;
}

CDamageScript::~CDamageScript()
{
}

void CDamageScript::tick()
{
	TextInfo m_Content;

	if (m_255 < 0.f)
		m_on = false;

	if (!m_on)
	{
		m_255 = 255.f;
		m_Content.Content = L"";
		return;
	}

	// 나중에 부딪힌 부분에서 damage 표시가 되도록 위치값을 수정해주세요!
	m_Content.Content = L"testetstsets";
	m_Content.FontColor = FONT_RGBA(255, 0, 0, m_255);
	m_Content.FontSize = 20.f;
	m_Content.FontPos = WorldPosToScreen(m_FirstPos); // 인자로 damage가 뜰 Pos를 넣어주세요
	m_255 -= 20.f * DT;
	m_FirstPos.y += DT;

	CTextMgr::GetInst()->AddText(m_Content);
}

Vec2 CDamageScript::WorldPosToScreen(const Vec3 _pos)
{
	Matrix viewMatrix = m_UIcamera->GetViewMat();
	Matrix projectionMatrix = m_UIcamera->GetProjMat();

	// 카메라의 뷰 행렬과 프로젝션 행렬을 얻어옵니다.
	// 월드 좌표를 카메라 좌표로 변환합니다.
	Vec3 cameraPos = XMVector3TransformCoord(_pos, viewMatrix);

	// 카메라 좌표를 클립 좌표로 변환합니다.
	Vec4 clipSpacePos = XMVector4Transform(Vec4(cameraPos.x, cameraPos.y, cameraPos.z, 1.f), projectionMatrix);

	// 클립 좌표를 NDC로 변환합니다.
	Vec3 ndcPos;
	ndcPos.x = clipSpacePos.x / clipSpacePos.w;
	ndcPos.y = clipSpacePos.y / clipSpacePos.w;

	// NDC 좌표를 스크린 좌표로 변환합니다.
	Vec2 screenPos;
	screenPos.x = (ndcPos.x + 1.6f) * 0.5f * CEngine::GetInst()->GetWindowResolution().x ;
	screenPos.y = (1.f - ndcPos.y) * 0.5f * CEngine::GetInst()->GetWindowResolution().y ;

	return screenPos;
}