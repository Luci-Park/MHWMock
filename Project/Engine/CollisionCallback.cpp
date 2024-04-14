#include "pch.h"
#include "CollisionCallback.h"

#include "CCollider3D.h"
#include "CGameObject.h"
#include "CPhysXMgr.h"

void CollisionCallback::onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count)
{
	PX_UNUSED(constraints);
	PX_UNUSED(count);
}

void CollisionCallback::onWake(physx::PxActor** actors, physx::PxU32 count)
{
	PX_UNUSED(actors);
	PX_UNUSED(count);
}

void CollisionCallback::onSleep(physx::PxActor** actors, physx::PxU32 count)
{
	PX_UNUSED(actors);
	PX_UNUSED(count);
}

void CollisionCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	pPXUSERDATA pUserData[2] = {};
	CCollider3D* pCollider[2] = {};


	for(UINT i = 0; i< nbPairs; ++i)
	{
		const PxContactPair& cp = pairs[i];


		pUserData[0] = (pPXUSERDATA)pairHeader.actors[0]->userData;
		pUserData[1] = (pPXUSERDATA)pairHeader.actors[1]->userData;
	
		if (nullptr == pUserData[0] || nullptr == pUserData[1])
			continue;
		

		pCollider[0] = pUserData[0]->pCollider;
		pCollider[1] = pUserData[1]->pCollider;

		CPhysXMgr::COLLISIONPAIR tCollisionPair;
		tCollisionPair.bTrigger = false;


		if (cp.flags & PxContactPairFlag::eREMOVED_SHAPE_0)
		{
			tCollisionPair.ePairFlag = physx::PxPairFlag::eNOTIFY_TOUCH_LOST;
			tCollisionPair.pFirst = nullptr;
			tCollisionPair.pSecond = pCollider[1]->GetOwner();
			CPhysXMgr::GetInst()->AddCallbackPair(tCollisionPair);
			return;
		}
		else if (cp.flags & PxContactPairFlag::eREMOVED_SHAPE_1)
		{
			tCollisionPair.ePairFlag = physx::PxPairFlag::eNOTIFY_TOUCH_LOST;
			tCollisionPair.pFirst = pCollider[0]->GetOwner();
			tCollisionPair.pSecond = nullptr;
			CPhysXMgr::GetInst()->AddCallbackPair(tCollisionPair);
			return;
		}


		if (physx::PxPairFlag::eNOTIFY_TOUCH_FOUND == (UINT)pairs[i].events)
		{
			if (pCollider[0] != nullptr && pCollider[1] != nullptr)
			{
				tCollisionPair.ePairFlag = physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
				tCollisionPair.pFirst = pCollider[0]->GetOwner();
				tCollisionPair.pSecond = pCollider[1]->GetOwner();
				CPhysXMgr::GetInst()->AddCallbackPair(tCollisionPair);
			}
			
		}
		else if (physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS == (UINT)pairs[i].events)
		{
			if (pCollider[0] != nullptr && pCollider[1] != nullptr)
			{
				tCollisionPair.ePairFlag = physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS;
				tCollisionPair.pFirst = pCollider[0]->GetOwner();
				tCollisionPair.pSecond = pCollider[1]->GetOwner();
				CPhysXMgr::GetInst()->AddCallbackPair(tCollisionPair);
			}
		}
		else if (physx::PxPairFlag::eNOTIFY_TOUCH_LOST == (UINT)pairs[i].events)
		{
			if (pCollider[0] != nullptr && pCollider[1] != nullptr)
			{
				tCollisionPair.ePairFlag = physx::PxPairFlag::eNOTIFY_TOUCH_LOST;
				tCollisionPair.pFirst = pCollider[0]->GetOwner();
				tCollisionPair.pSecond = pCollider[1]->GetOwner();
				CPhysXMgr::GetInst()->AddCallbackPair(tCollisionPair);
			}
		}
	}
}

void CollisionCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
	for (UINT i = 0; i < count; ++i)
	{
		pPXUSERDATA pUserData[2] = {};
		CCollider3D* pCollider[2] = {};

		pUserData[0] = (pPXUSERDATA)pairs[i].otherActor->userData;
		pUserData[1] = (pPXUSERDATA)pairs[i].triggerActor->userData;

		//Collider 컴포넌트가 해제되어 pUserData가 nullptr인 경우의 예외처리.
		if (nullptr == pUserData[0] || nullptr == pUserData[1])
			continue;

		pCollider[0] = pUserData[0]->pCollider;
		pCollider[1] = pUserData[1]->pCollider;

		CPhysXMgr::COLLISIONPAIR tCollisionPair;
		tCollisionPair.bTrigger = true;

		if (physx::PxPairFlag::eNOTIFY_TOUCH_FOUND == pairs[i].status)
		{
			if (pCollider[0] != nullptr && pCollider[1] != nullptr)
			{
				tCollisionPair.ePairFlag = physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
				tCollisionPair.pFirst = pCollider[0]->GetOwner();
				tCollisionPair.pSecond = pCollider[1]->GetOwner();
				CPhysXMgr::GetInst()->AddCallbackPair(tCollisionPair);
			}
		}
		else if (physx::PxPairFlag::eNOTIFY_TOUCH_LOST == pairs[i].status)
		{
			if (pCollider[0] != nullptr && pCollider[1] != nullptr)
			{
				tCollisionPair.ePairFlag = physx::PxPairFlag::eNOTIFY_TOUCH_LOST;
				tCollisionPair.pFirst = pCollider[0]->GetOwner();
				tCollisionPair.pSecond = pCollider[1]->GetOwner();
				CPhysXMgr::GetInst()->AddCallbackPair(tCollisionPair);
			}
		}
	}
}

void CollisionCallback::onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count)
{
}
