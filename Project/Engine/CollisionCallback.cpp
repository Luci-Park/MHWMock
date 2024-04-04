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
		pUserData[0] = (pPXUSERDATA)pairHeader.actors[0]->userData;
		pUserData[1] = (pPXUSERDATA)pairHeader.actors[1]->userData;
	
		if (nullptr == pUserData[0] || nullptr == pUserData[1])
			continue;

		// 바닥 충돌 체크

		/*PxContactPairPoint* contactPointBuffer = new PxContactPairPoint[16];

		UINT nCount = pairs[i].extractContacts(contactPointBuffer, 16);
		
		if (physx::PxPairFlag::eNOTIFY_TOUCH_FOUND == pairs[i].events || physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS == pairs[i].events)
		{
			if (((pPXUSERDATA)(pairs[i].shapes[0]->getActor()->userData))->bGround == false)
			{
				for (UINT j = 0; j < nCount; ++j)
				{
					if (contactPointBuffer[j].normal.y >= 0.9f)
					{
						PxActor* pActor = pairs[i].shapes[0]->getActor();
						((pPXUSERDATA)(pActor->userData))->bGround = true;
						break;
					}
				}
			}
		}
		else
		{
			if (((pPXUSERDATA)(pairs[i].shapes[0]->getActor()->userData))->bGround == true)
			{
				if (0 == nCount)
					((pPXUSERDATA)(pairs[i].shapes[0]->getActor()->userData))->bGround = false;

				for (UINT j = 0; j < nCount; ++j)
				{
					if (contactPointBuffer[j].normal.y >= 0.9f)
					{
						((pPXUSERDATA)(pairs[i].shapes[0]->getActor()->userData))->bGround = false;
						break;
					}
				}
			}
		}
		delete[] contactPointBuffer;*/

		pCollider[0] = pUserData[0]->pCollider;
		pCollider[1] = pUserData[1]->pCollider;

		CPhysXMgr::COLLISIONPAIR tCollisionPair;
		tCollisionPair.bTrigger = false;



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
				/*PxActor* pActor = pairs[i].shapes[0]->getActor();
				if (pairHeader.actors[0]->getType() == PxActorType::eRIGID_DYNAMIC 
					|| (pairHeader.actors[1]->getType() == PxActorType::eRIGID_DYNAMIC))
				{
					pairHeader.actors[0]->is<PxRigidDynamic>()->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
					pairHeader.actors[0]->is<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));

					pairHeader.actors[1]->is<PxRigidDynamic>()->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
					pairHeader.actors[1]->is<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
				}*/

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
