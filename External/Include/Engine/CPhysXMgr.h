#pragma once
#include "CSingleton.h"

#include <PxPhysics.h>
#include <PxPhysicsApi.h>

// PhysX Library
#ifdef _DEBUG
#pragma comment(lib, "PhysX//PhysX_64")
#pragma comment(lib, "PhysX//PhysXFoundation_64")
#pragma comment(lib, "PhysX//PhysXExtensions_static_64")
#pragma comment(lib, "PhysX//PhysXPvdSDK_static_64")
#else
#pragma comment(lib, "Script//PhysX_64")
#pragma comment(lib, "Script//PhysXFoundation_64")
#pragma comment(lib, "Script//PhysXExtensions_static_64")
#pragma comment(lib, "PhysX//PhysXPvdSDK_static_64")
#endif


class CPhysXMgr : public CSingleton<CPhysXMgr>
{
private:
	// declare variables
	physx::PxDefaultAllocator			mDefaultAllocatorCallback;
	physx::PxDefaultErrorCallback		mDefaultErrorCallback;
	physx::PxDefaultCpuDispatcher* mDispatcher = NULL;
	physx::PxTolerancesScale				mToleranceScale;

	physx::PxFoundation* mFoundation = NULL;
	physx::PxPhysics* mPhysics = NULL;

	physx::PxScene* mScene = NULL;
	physx::PxMaterial* mMaterial = NULL;

	physx::PxPvd* mPvd = NULL;

	bool m_bSimulate;

public:
	void init();
	void process();

public:
	void tick();
	void render();

public:
	void CreateSimulation();

public:
	CPhysXMgr();
	~CPhysXMgr();
};

