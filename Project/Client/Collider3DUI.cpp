#include "pch.h"
#include "Collider3DUI.h"

#include "Engine\CGameObject.h"
#include "Engine\CCollider3D.h"

using namespace physx;

Collider3DUI::Collider3DUI()
	: ComponentUI("##Coillider3D",COMPONENT_TYPE::COLLIDER3D)
	, _GravityFlag(true)
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

	ImGui::Checkbox("Edit Collider Size", &_EditSize);

	if (_EditSize)
	{
		SHAPE_TYPE shapeType = GetTarget()->Collider3D()->GetShapeType();
		if (shapeType == SHAPE_TYPE::CUBE)
		{
			ImGui::Text("halfExtents");
			ImGui::SameLine();
			ImGui::DragFloat3("##halfExtents", _HalfExtents);

			GetTarget()->Collider3D()->EditBoxShape(_HalfExtents);
		}
		else if (shapeType == SHAPE_TYPE::CAPSULE)
		{
			ImGui::Text("Radius");
			ImGui::SameLine();
			ImGui::DragFloat("##Radius", &_Radius);
			ImGui::Text("halfHeight");
			ImGui::SameLine();
			ImGui::DragFloat("##halfHeight", &_HalfHeight);

			GetTarget()->Collider3D()->EditCapsuleShape(_Radius, _HalfHeight);
		}
		else if (shapeType == SHAPE_TYPE::CONVEX)
		{
			ImGui::Text("Scale");
			ImGui::SameLine();
			ImGui::DragFloat3("##Scale", _ScaleVec);

			GetTarget()->Collider3D()->EditConvexShape(_ScaleVec);
		}
	}

	if (type == ACTOR_TYPE::DYNAMIC)
	{
		PxRigidActor* actor = GetTarget()->Collider3D()->GetRigidActor();
		ImGui::Checkbox("Gravity", &_Gravity);
		if (_Gravity && _GravityFlag)
		{
			GetTarget()->Collider3D()->SetGravity(_Gravity);
			_GravityFlag = false;
		}
		else if (!_Gravity && !_GravityFlag)
		{
			GetTarget()->Collider3D()->SetGravity(_Gravity);
			_GravityFlag = true;
		}

		auto velocity = actor->is<PxRigidDynamic>()->getLinearVelocity();
		ImGui::Text("Velocity: X: %f Y: %f Z: %f", velocity.x, velocity.y, velocity.z);

		PxBounds3 bounds = actor->getWorldBounds();
		PxVec3 scale = bounds.getExtents();
		ImGui::Text("Scale: X: %f Y: %f Z: %f", scale.x, scale.y, scale.z);
	}
	else if (type == ACTOR_TYPE::STATIC)
	{
		PxRigidActor* actor = GetTarget()->Collider3D()->GetRigidActor();
		PxBounds3 bounds = actor->getWorldBounds();
		PxVec3 scale = bounds.getExtents();
		ImGui::Text("Scale: X: %f Y: %f Z: %f", scale.x, scale.y, scale.z);
	}


	return TRUE;
}
