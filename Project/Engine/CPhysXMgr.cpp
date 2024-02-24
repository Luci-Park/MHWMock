#include "pch.h"
#include "CPhysXMgr.h"

#include <PxPhysics.h>
#include <PxPhysicsApi.h>

#include "CollisionCallback.h"

#include "CKeyMgr.h"
#include "CRenderMgr.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CCollider3D.h"
#include "CCollisionMgr.h"

PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// 두 객체가 모두 그룹이면 충돌을 비활성화
	if ((filterData0.word1 & filterData1.word0) != filterData1.word0)
	{
		return PxFilterFlag::eSUPPRESS;
	}

	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST | PxPairFlag::eSOLVE_CONTACT | PxPairFlag::eDETECT_DISCRETE_CONTACT;
		return PxFilterFlag::eDEFAULT;
	}

	// all initial and persisting reports for everything, with per-point data
	pairFlags = PxPairFlag::eSOLVE_CONTACT | PxPairFlag::eDETECT_DISCRETE_CONTACT
		| PxPairFlag::eNOTIFY_TOUCH_FOUND
		| PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| PxPairFlag::eNOTIFY_TOUCH_LOST
		| PxPairFlag::eNOTIFY_CONTACT_POINTS;

	return PxFilterFlag::eDEFAULT;
}

CPhysXMgr::CPhysXMgr()
	: m_pFoundation(nullptr)
	, m_pPhysics(nullptr)
	, m_pDispatcher(nullptr)
	, m_pMaterial(nullptr)
	, m_pPvd(nullptr)
	, m_pScene(nullptr)
	, m_pCollisionCallback(nullptr)
	, m_bSimulate(false)
{
}
CPhysXMgr::~CPhysXMgr()
{
	/*if (m_bSimulate)
		while (false == (mScene->fetchResults(false)));
	delete mScene->getSimulationEventCallback();*/
	delete m_pScene->getSimulationEventCallback();
	PX_RELEASE(m_pScene);
	PX_RELEASE(m_pDispatcher);

	// Cooking 생성시 rick제거.
	//PX_RELEASE(m_pCooking);

	PX_RELEASE(m_pPhysics);

	if (m_pPvd)
	{
		PxPvdTransport* pPVDTransport = m_pPvd->getTransport();
		PX_RELEASE(m_pPvd);
		PX_RELEASE(pPVDTransport);
	}

	PX_RELEASE(m_pFoundation);

	//PX_RELEASE(m_pMaterial);
}



void CPhysXMgr::init()
{
	m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);


	if (!m_pFoundation) throw("PxCreateFoundation failed!");
	
	//PhysX Visual Debugger
	m_pPvd = PxCreatePvd(*m_pFoundation);
	
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	
	m_pPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
	

	mToleranceScale.length = 100;        // typical length of an object
	mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice
	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, mToleranceScale, true, m_pPvd);


	PxSceneDesc sceneDesc(m_pPhysics->getTolerancesScale());

	// 중력설정.
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	m_pDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = m_pDispatcher;

	// 물리용 Shader 교체
	//sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	sceneDesc.filterShader = contactReportFilterShader;
	
	m_pScene = m_pPhysics->createScene(sceneDesc);
	m_pScene->setSimulationEventCallback(new CollisionCallback);

	m_pMaterial = m_pPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	m_pPvdClient = m_pScene->getScenePvdClient();

	if (m_pPvdClient)
	{
		m_pPvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		m_pPvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		m_pPvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	// FilterData Group설정.
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_FilterData[i].word0 = (1 << i+1);
		m_FilterData[i].word1 = 0;
	}

}

void CPhysXMgr::process()
{
	tick();
	SimulatePhysX();
}

void CPhysXMgr::tick()
{
	if (true == m_bSimulate || nullptr == m_pScene)
		return;

	//Update all of Actor's info
	PxU32		nNumActors = 0;
	PxActor** ppActors = nullptr;
	bool bFilterChange = CCollisionMgr::GetInst()->GetCollisionChange();

	nNumActors = m_pScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC);
	ppActors = new PxActor * [nNumActors];
	m_pScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, ppActors, nNumActors);
	for (UINT i = 0; i < nNumActors; ++i)
	{
		if (ppActors[i]->userData)
		{
			CCollider3D* pCollider = ((pPXUSERDATA)(ppActors[i]->userData))->pCollider;
			pCollider->UpdateActorInfo();
			
			if (bFilterChange)
			{
				pCollider->ChangeFilterData();
			}
		}
	}
	delete[] ppActors;

	nNumActors = m_pScene->getNbActors(PxActorTypeFlag::eRIGID_STATIC);

	ppActors = new PxActor * [nNumActors];

	m_pScene->getActors(PxActorTypeFlag::eRIGID_STATIC, ppActors, nNumActors);
	for (UINT i = 0; i < nNumActors; ++i)
	{
		if (ppActors[i]->userData)
		{
			CCollider3D* pCollider = ((pPXUSERDATA)(ppActors[i]->userData))->pCollider;
			pCollider->UpdateActorInfo();

			if (bFilterChange)
			{
				pCollider->ChangeFilterData();
			}
		}
	}
	delete[] ppActors;

	CCollisionMgr::GetInst()->SetCollisionChange(false);
}

void CPhysXMgr::SimulatePhysX()
{
	//실제 시뮬레이션 돌리는 부분 여기서 피직스를 계산
	m_pScene->simulate(1.0f / 60.0f);

	m_bSimulate = true;
}

//시뮬레이션 결과 값 가져옴
void CPhysXMgr::FetchResults()
{
	if (false == m_bSimulate || nullptr == m_pScene)
		return;

	while (false == (m_pScene->fetchResults(true)));

	for (auto& rPair : m_lCallback)
	{
		if (rPair.bTrigger == false)
		{
			switch (rPair.ePairFlag)
			{
			case PxPairFlag::Enum::eNOTIFY_TOUCH_FOUND:
				if (rPair.pFirst && rPair.pSecond)
				{
					rPair.pFirst->Collider3D()->OnCollisionEnter(rPair.pSecond->Collider3D());
					rPair.pSecond->Collider3D()->OnCollisionEnter(rPair.pFirst->Collider3D());
				}
				break;
			case PxPairFlag::Enum::eNOTIFY_TOUCH_PERSISTS:
				if (rPair.pFirst && rPair.pSecond)
				{
					rPair.pFirst->Collider3D()->OnCollisionStay(rPair.pSecond->Collider3D());
					rPair.pSecond->Collider3D()->OnCollisionStay(rPair.pFirst->Collider3D());
				}
				break;
			case PxPairFlag::Enum::eNOTIFY_TOUCH_LOST:
				if (rPair.pFirst && rPair.pSecond)
				{
					rPair.pFirst->Collider3D()->OnCollisionExit(rPair.pSecond->Collider3D());
					rPair.pSecond->Collider3D()->OnCollisionExit(rPair.pFirst->Collider3D());
				}
				break;
			default:
				break;
			}
		}
		else
		{
			switch (rPair.ePairFlag)
			{
			case PxPairFlag::Enum::eNOTIFY_TOUCH_FOUND:
				if (rPair.pFirst && rPair.pSecond)
				{
					rPair.pFirst->Collider3D()->OnTriggerEnter(rPair.pSecond->Collider3D());
					rPair.pSecond->Collider3D()->OnTriggerEnter(rPair.pFirst->Collider3D());
				}
				break;
			case PxPairFlag::Enum::eNOTIFY_TOUCH_LOST:
				if (rPair.pFirst && rPair.pSecond)
				{
					rPair.pFirst->Collider3D()->OnTriggerExit(rPair.pSecond->Collider3D());
					rPair.pSecond->Collider3D()->OnTriggerExit(rPair.pFirst->Collider3D());
				}
				break;
			default:
				break;
			}
		}
	}

	m_lCallback.clear();

	// 시물레이션 도중 Transform 변환 정보 전달. ..~~
	SetTransformResult();

	m_bSimulate = false;
}

void CPhysXMgr::SetTransformResult()
{
	CGameObject* obj;
	PxU32 nNumActors = 0;
	PxRigidDynamic** ppDynamicActors = nullptr;

	nNumActors = m_pScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC);

	if (nNumActors > 0) {
		ppDynamicActors = new PxRigidDynamic * [nNumActors];
		m_pScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, (PxActor**)&ppDynamicActors[0], nNumActors);

		// 각 다이나믹 액터의 위치 값을 가져옴
		for (PxU32 i = 0; i < nNumActors; ++i) {
			obj = ((pPXUSERDATA)(ppDynamicActors[i]->userData))->pCollider->GetOwner();
			PxTransform transform = ppDynamicActors[i]->getGlobalPose();
			PxVec3 position = transform.p;
			PxQuat rotation = transform.q;

			// 가져온 위치 값을 사용하여 오브젝트의 위치 변경
			Vec3 pos = Vec3(position.x, position.y, position.z);
			Vec3 objPos = obj->Transform()->GetRelativePos();
			objPos +=pos;
			obj->Transform()->SetRelativePos(pos);
		}

		delete[] ppDynamicActors;
	}
}

void CPhysXMgr::CreateSimulation()
{	
	// create simulation
	PxRigidStatic* groundPlane = PxCreatePlane(*m_pPhysics, PxPlane(0, 1, 0, 50), *m_pMaterial);
	m_pScene->addActor(*groundPlane);

	float halfExtent = .5f;
	PxShape* shape = m_pPhysics->createShape(PxBoxGeometry(halfExtent, halfExtent, halfExtent), *m_pMaterial);
	PxU32 size = 30;
	PxTransform t(PxVec3(0));
	for (PxU32 i = 0; i < size; i++) {
		for (PxU32 j = 0; j < size - i; j++) {
			PxTransform localTm(PxVec3(PxReal(j * 2) - PxReal(size - i), PxReal(i * 2 + 1), 0) * halfExtent);
			PxRigidDynamic* body = m_pPhysics->createRigidDynamic(t.transform(localTm));
			body->attachShape(*shape);
			PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
			m_pScene->addActor(*body);
		}
	}
	shape->release();
}

PxRigidDynamic* CPhysXMgr::createDynamic(const PxGeometry& geometry, const PxVec3& velocity)
{
	PxRigidDynamic* dynamic = PxCreateDynamic(*m_pPhysics, PxTransform(PxVec3(0.0f, 10.0f, 30.0f)), geometry, *m_pMaterial, 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);
	dynamic->setMass(1.0f);
	m_pScene->addActor(*dynamic);
	return dynamic;
}

void CPhysXMgr::AddActor(PxActor& _Actor)
{
	m_pScene->addActor(_Actor);
}


