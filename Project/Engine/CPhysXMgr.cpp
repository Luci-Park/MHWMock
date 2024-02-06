#include "pch.h"
#include "CPhysXMgr.h"

#include <PxPhysics.h>
#include <PxPhysicsApi.h>

#include "CKeyMgr.h"
#include "CRenderMgr.h"
#include "CCamera.h"
#include "CTransform.h"

CPhysXMgr::CPhysXMgr()
{
}
CPhysXMgr::~CPhysXMgr()
{
	/*if (m_bSimulate)
		while (false == (mScene->fetchResults(false)));
	delete mScene->getSimulationEventCallback();*/
	PX_RELEASE(mScene);

	PX_RELEASE(mDispatcher);

	// Cooking 생성시 rick제거.
	//PX_RELEASE(m_pCooking);

	PX_RELEASE(mPhysics);

	if (mPvd)
	{
		physx::PxPvdTransport* pPVDTransport = mPvd->getTransport();
		PX_RELEASE(mPvd);
		PX_RELEASE(pPVDTransport);
	}

	PX_RELEASE(mFoundation);
}

void CPhysXMgr::init()
{
	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
	
	if (!mFoundation) throw("PxCreateFoundation failed!");
	
	mPvd = PxCreatePvd(*mFoundation);
	
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	
	mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
	
	mToleranceScale.length = 100;        // typical length of an object
	mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice
	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);

	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());

	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = mDispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

	mScene = mPhysics->createScene(sceneDesc);

	pvdClient = mScene->getScenePvdClient();

	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	CreateSimulation();
}

void CPhysXMgr::process()
{
	tick();
	render();
}

void CPhysXMgr::tick()
{
	//// Sphere충돌체 발사.
	//{
	//	if (KEY_TAP(KEY::SPACE))
	//	{
	//		createDynamic(PxSphereGeometry(3.0f), PxVec3(0, 0, -1) * 200);
	//	}
	//}

	//// PVD Camera 위치 동일하게 해주도록
	//{
	//	CCamera* m_EditorCam = CRenderMgr::GetInst()->GetEditorCam();

	//	Vec3 vCamPos = m_EditorCam->GetOwner()->Transform()->GetWorldPos();

	//	Matrix mCamWorldMatrix = m_EditorCam->GetOwner()->Transform()->GetWorldMat();
	//	Vec3 vCamUp = mCamWorldMatrix.Up();
	//	Vec3 vCamFront = mCamWorldMatrix.Front();

	//	if (pvdClient) {
	//		pvdClient->updateCamera("Default", PxVec3(vCamPos.x, vCamPos.y, -vCamPos.z), PxVec3(vCamUp.x, vCamUp.y, -vCamUp.z), PxVec3(vCamFront.x, vCamFront.y, -vCamFront.z));
	//	}
	//}



	mScene->simulate(1.0f / 60.0f);
	mScene->fetchResults(true);
}

void CPhysXMgr::render()
{
}

void CPhysXMgr::CreateSimulation()
{	
	// create simulation
	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	mScene->addActor(*groundPlane);

	float halfExtent = .5f;
	physx::PxShape* shape = mPhysics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *mMaterial);
	physx::PxU32 size = 30;
	physx::PxTransform t(physx::PxVec3(0));
	for (physx::PxU32 i = 0; i < size; i++) {
		for (physx::PxU32 j = 0; j < size - i; j++) {
			physx::PxTransform localTm(physx::PxVec3(physx::PxReal(j * 2) - physx::PxReal(size - i), physx::PxReal(i * 2 + 1), 0) * halfExtent);
			physx::PxRigidDynamic* body = mPhysics->createRigidDynamic(t.transform(localTm));
			body->attachShape(*shape);
			physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
			mScene->addActor(*body);
		}
	}
	shape->release();
}

PxRigidDynamic* CPhysXMgr::createDynamic(const PxGeometry& geometry, const PxVec3& velocity)
{
	PxRigidDynamic* dynamic = PxCreateDynamic(*mPhysics, PxTransform(PxVec3(0.0f, 10.0f, 30.0f)), geometry, *mMaterial, 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);
	mScene->addActor(*dynamic);
	return dynamic;
}


