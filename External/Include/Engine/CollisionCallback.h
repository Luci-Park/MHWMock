#pragma once
#include "PxPhysicsAPI.h"

class CollisionCallback : public physx::PxSimulationEventCallback
{
public:
	// PxSimulationEventCallback을(를) 통해 상속됨
	virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override;
	virtual void onWake(physx::PxActor** actors, physx::PxU32 count) override;
	virtual void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
	virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;
	virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
	virtual void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override;
};

