#pragma once
#include "CSingleton.h"

#include <PxPhysics.h>
#include <PxPhysicsApi.h>
#include <cooking/PxCooking.h>

// PhysX Library
#ifdef _DEBUG
#pragma comment(lib, "PhysX_64")
#pragma comment(lib, "PhysXFoundation_64")
#pragma comment(lib, "PhysXExtensions_static_64")
#pragma comment(lib, "PhysXPvdSDK_static_64")
#pragma comment(lib, "PhysXCooking_64")
#pragma comment(lib, "PhysXCommon_64")
#else
#pragma comment(lib, "PhysX_64")
#pragma comment(lib, "PhysXFoundation_64")
#pragma comment(lib, "PhysXExtensions_static_64")
#pragma comment(lib, "PhysXPvdSDK_static_64")
#pragma comment(lib, "PhysXCooking_64")
#endif

using namespace physx;

class CollisionCallback;
class CPhysXMgr : public CSingleton<CPhysXMgr>
{
public:
	typedef struct tCollisionPair
	{
		bool							bTrigger;
		physx::PxPairFlag::Enum			ePairFlag;
		CGameObject*					pFirst;
		CGameObject*					pSecond;
	}COLLISIONPAIR, *pCOLLISIONPAIR;


private:
	PxDefaultAllocator			mDefaultAllocatorCallback;
	PxDefaultErrorCallback		mDefaultErrorCallback;
	PxDefaultCpuDispatcher*		m_pDispatcher = NULL;
	PxTolerancesScale			mToleranceScale;

	PxFoundation*		m_pFoundation = NULL;
	PxPhysics*			m_pPhysics = NULL;

	PxScene*			m_pScene = NULL;
	PxMaterial*			m_pMaterial = NULL;

	PxPvd*				m_pPvd = NULL;
	PxPvdSceneClient*	m_pPvdClient;

	//Cooking
	//PxCooking* m_pCooking;

	CollisionCallback*	m_pCollisionCallback;
	bool				m_bSimulate;

	PxFilterData		m_FilterData[MAX_LAYER];

	std::list<tCollisionPair> m_lCallback;

public:
	void CreateSimulation();
	PxRigidDynamic* createDynamic(const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));

public:
	void AddActor(PxActor& _Actor);
	void AddCallbackPair(const COLLISIONPAIR _tCollsionPair) {m_lCallback.emplace_back(_tCollsionPair);}

public:
	PxPhysics* GetPxPhysics() { return m_pPhysics; }
	PxMaterial* GetDefaultMaterial() { return m_pMaterial; }
	PxFilterData GetPxFilterData(UINT _Idx) { return m_FilterData[_Idx]; }

public:
	void SetPxFilterData(PxFilterData _FilterData, UINT _Idx) { m_FilterData[_Idx] = _FilterData; }
public:
	void SetTransformResult();
public:
	void init();
	void process();
	void tick();
	void FetchResults();

public:
	CPhysXMgr();
	~CPhysXMgr();
};

