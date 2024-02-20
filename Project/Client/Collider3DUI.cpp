#include "pch.h"
#include "Collider3DUI.h"

#include "Engine\CGameObject.h"
#include "Engine\CCollider3D.h"

using namespace physx;

Collider3DUI::Collider3DUI()
	: ComponentUI("##Coillider3D",COMPONENT_TYPE::COLLIDER3D)
{
	SetName("Coillider3D");
}

Collider3DUI::~Collider3DUI()
{
}

int Collider3DUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;

	ACTOR_TYPE type = GetTarget()->Collider3D()->GetActorType();
	PxRigidActor* actor = GetTarget()->Collider3D()->GetRigidActor();

	if (type == ACTOR_TYPE::DYNAMIC)
	{
		ImGui::Checkbox("Gravity", &_Gravity);
		GetTarget()->Collider3D()->SetGravity(_Gravity);

		auto velocity = actor->is<PxRigidDynamic>()->getLinearVelocity();
		ImGui::Text("Velocity: X: %f Y: %f Z: %f", velocity.x, velocity.y, velocity.z);

		PxBounds3 bounds = actor->getWorldBounds();
		PxVec3 scale = bounds.getExtents();
		ImGui::Text("Scale: X: %f Y: %f Z: %f", scale.x, scale.y, scale.z);
	}
	else if (type == ACTOR_TYPE::STATIC)
	{
		PxBounds3 bounds = actor->getWorldBounds();
		PxVec3 scale = bounds.getExtents();
		ImGui::Text("Scale: X: %f Y: %f Z: %f", scale.x, scale.y, scale.z);
	}

	return TRUE;
}
