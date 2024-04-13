#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CResMgr.h"
#include "CTransform.h"
#include "CTimeMgr.h"

#include "CKeyMgr.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_RWBuffer(nullptr)
	, m_ModuleData{}
	, m_AnimeData{}
	, m_AccTime(0.f)
	, m_ParticleTexture(nullptr)
	, m_IsAnime(false)
	, m_AnimeDataBuffer(nullptr)
	, m_Frames{}
	, m_AnimeIdx(0)
{
	m_ModuleData.iMaxParticleCount = 3000;
	
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
	m_ModuleData.SpawnRate = 50;
	m_ModuleData.vSpawnColor = Vec3(0.4f, 1.f, 0.4f);
	m_ModuleData.vSpawnScaleMin = Vec3(15.f, 15.f, 1.f);
	m_ModuleData.vSpawnScaleMax = Vec3(20.f, 20.f, 1.f);

	m_ModuleData.SpawnShapeType = 0;
	m_ModuleData.vBoxShapeScale = Vec3(200.f, 200.f, 200.f);	
	m_ModuleData.Space = 0; // 시뮬레이션 좌표계

	m_ModuleData.MinLifeTime = 3.f;
	m_ModuleData.MaxLifeTime = 5.f;

	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = true;
	m_ModuleData.StartScale = 1.5f;
	m_ModuleData.EndScale = 0.2f;

	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = true;
	m_ModuleData.vStartColor = Vec3(0.2f, 0.3f, 1.0f);
	m_ModuleData.vEndColor = Vec3(0.4f, 1.f, 0.4f);

	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = true;
	m_ModuleData.AddVelocityType = 0; // From Center
	m_ModuleData.Speed = 300.f;
	m_ModuleData.vVelocityDir = Vec3(0.f, 1.f, 0.f);
	m_ModuleData.OffsetAngle;

	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = true;
	m_ModuleData.StartDrag = 500.f;
	m_ModuleData.EndDrag = -500.f;

	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = false;
	m_ModuleData.fNoiseTerm = 1.f;
	m_ModuleData.fNoiseForce = 100.f;

	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = true;
	m_ModuleData.VelocityAlignment = true;
	m_ModuleData.VelocityScale = true;
	m_ModuleData.vMaxVelocityScale = Vec3(15.f, 1.f, 1.f);
	m_ModuleData.vMaxSpeed = 500.f;

	m_AnimeData.vSize = Vec2(1.f, 1.f);
	m_AnimeData.vLeftTop = Vec2(0.f, 0.f);

	// 입자 메쉬
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"PointMesh"));

	// 파티클 전용 재질
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleRenderMtrl"));
	// 파티클 업데이트 컴퓨트 쉐이더	
	m_UpdateCS = (CParticleUpdateShader*)CResMgr::GetInst()->FindRes<CComputeShader>(L"ParticleUpdateCS").Get();
	m_ParticleTexture = CResMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Bubbles99px.png", L"texture\\particle\\Bubbles99px.png");

	// 파티클 버퍼
	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_ModuleData.iMaxParticleCount, SB_TYPE::READ_WRITE, false);

	// 파티클 스폰 개수 전달용 버퍼
	m_RWBuffer = new CStructuredBuffer;
	m_RWBuffer->Create(sizeof(tRWParticleBuffer), 1, SB_TYPE::READ_WRITE, true);

	// 모듈 활성화 및 모듈 설정 정보 버퍼
	m_ModuleDataBuffer = new CStructuredBuffer;
	m_ModuleDataBuffer->Create(sizeof(tParticleModule), 1, SB_TYPE::READ_ONLY, true);

	m_AnimeDataBuffer = new CStructuredBuffer;
	m_AnimeDataBuffer->Create(sizeof(tParticleAnime), 1, SB_TYPE::READ_ONLY, true);
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;

	if (nullptr != m_RWBuffer)
		delete m_RWBuffer;

	if (nullptr != m_ModuleDataBuffer)
		delete m_ModuleDataBuffer;
}


void CParticleSystem::finaltick()
{
	// 스폰 레이트 계산
	// 1개 스폰 시간
	float fTimePerCount = 1.f / (float)m_ModuleData.SpawnRate;
	m_AccTime += DT;

	// 누적시간이 개당 생성시간을 넘어서면
	if (fTimePerCount < m_AccTime)
	{
		// 초과 배율 ==> 생성 개수
		float fData = m_AccTime / fTimePerCount;

		// 나머지는 남은 시간
		m_AccTime = fTimePerCount * (fData - floor(fData));

		// 버퍼에 스폰 카운트 전달
		tRWParticleBuffer rwbuffer = { (int)fData, };		
		m_RWBuffer->SetData(&rwbuffer);
	}

	if (m_IsAnime)
	{
		//update anime data
		Vec2 Resolution = Vec2(m_ParticleTexture->Width(), m_ParticleTexture->Height());
		m_Frames.clear();
		for (int i = 0; i < m_AnimeXY.x; i++)
		{
			AnimeFrame frame = {};
			frame.vSize = (Resolution/ m_AnimeXY) / Resolution;
			frame.vLeftTop.x = frame.vSize.x * i;
			frame.vLeftTop.y = 0;
			frame.fDuration = 1 / m_AnimeXY.x;
			m_Frames.push_back(frame);
		}
	}

	// 파티클 업데이트 컴퓨트 쉐이더
	m_ModuleDataBuffer->SetData(&m_ModuleData);

	m_UpdateCS->SetParticleBuffer(m_ParticleBuffer);
	m_UpdateCS->SetRWParticleBuffer(m_RWBuffer);
	m_UpdateCS->SetModuleData(m_ModuleDataBuffer);
	m_UpdateCS->SetNoiseTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\noise\\noise_01.png"));
	m_UpdateCS->SetParticleObjectPos(Transform()->GetWorldPos());

	m_UpdateCS->Execute();
}

void CParticleSystem::render()
{
	Transform()->UpdateData();

	if (m_IsAnime)
	{
		//update anime data
		m_AnimeTime += DT;
		if (m_AnimeTime > m_Frames[m_AnimeIdx].fDuration)
		{
			if (m_AnimeIdx < m_AnimeXY.x-1)
				m_AnimeIdx++;
			else
				m_AnimeIdx = 0;

			m_AnimeTime = 0;
		}

		m_AnimeData.bIsAnime = m_IsAnime;
		m_AnimeData.vLeftTop = m_Frames[m_AnimeIdx].vLeftTop;
		m_AnimeData.vSize = m_Frames[m_AnimeIdx].vSize;

		//Set Particle anim data
		m_AnimeDataBuffer->SetData(&m_AnimeData);
	}

	// 파티클버퍼 t20 에 바인딩
	m_ParticleBuffer->UpdateData(20, PIPELINE_STAGE::PXS_ALL);

	// 모듈 데이터 t21 에 바인딩
	m_ModuleDataBuffer->UpdateData(21, PIPELINE_STAGE::PS_GEOMETRY);

	//Particle anime data bind at t22
	m_AnimeDataBuffer->UpdateData(22, PIPELINE_STAGE::PXS_ALL);

	// Particle Render	
	GetMaterial()->SetTexParam(TEX_0, m_ParticleTexture);

	GetMaterial()->UpdateData();
	GetMesh()->render_particle(m_ModuleData.iMaxParticleCount);

	// 파티클 버퍼 바인딩 해제
	m_ParticleBuffer->Clear();
	m_ModuleDataBuffer->Clear();
	m_AnimeDataBuffer->Clear();
}

void CParticleSystem::SaveToLevelFile(FILE* _File)
{
	CRenderComponent::SaveToLevelFile(_File);
	
	fwrite(&m_ModuleData, sizeof(tParticleModule), 1, _File);
	SaveResRef(m_UpdateCS.Get(), _File);
}

void CParticleSystem::LoadFromLevelFile(FILE* _File)
{
	CRenderComponent::LoadFromLevelFile(_File);

	fread(&m_ModuleData, sizeof(tParticleModule), 1, _File);

	int i = 0;
	fread(&i, sizeof(i), 1, _File);

	if (i)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _File);
		LoadWString(strRelativePath, _File);

		m_UpdateCS = (CParticleUpdateShader*)CResMgr::GetInst()->FindRes<CComputeShader>(strKey).Get();
	}
}
