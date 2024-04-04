#include "pch.h"
#include "Collider3DUI.h"

#include "Engine\CGameObject.h"
#include "Engine\CCollider3D.h"

using namespace physx;

Collider3DUI::Collider3DUI()
	: ComponentUI("##Coillider3D", COMPONENT_TYPE::COLLIDER3D)
	, _GravityFlag(true)
	, _EditSize(false)
	, _Gravity(false)
	, _Ground(false)
	, _Radius(1.f)
	, _HalfHeight(1.f)
	, _ScaleVec(Vec3(1.f, 1.f, 1.f))
	, _HalfExtents(Vec3(1.f, 1.f, 1.f))
	, _OffSetPos(Vec3::Zero)
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

	ImGui::Checkbox("Edit Collider Size", &_EditSize);

	if (_EditSize)
	{
		_OffSetPos = GetTarget()->Collider3D()->GetOffsetPos();
		ImGui::Text("OffsetPos");
		ImGui::SameLine();
		ImGui::DragFloat3("##OffsetPos", _OffSetPos);
		GetTarget()->Collider3D()->SetOffsetPos(_OffSetPos);

		SHAPE_TYPE shapeType = GetTarget()->Collider3D()->GetShapeType();
		if (shapeType == SHAPE_TYPE::CUBE)
		{
			_HalfExtents = GetTarget()->Collider3D()->GetBoxExtents();
			ImGui::Text("halfExtents");
			ImGui::SameLine();
			ImGui::DragFloat3("##halfExtents", _HalfExtents);

			GetTarget()->Collider3D()->EditBoxShape(_HalfExtents);
		}
		else if (shapeType == SHAPE_TYPE::CAPSULE)
		{
			_Radius = GetTarget()->Collider3D()->GetCapsuleRadius();
			_HalfHeight = GetTarget()->Collider3D()->GetCapsuleHalfHeight();
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

		_Ground = GetTarget()->Collider3D()->GetGround();
		ImGui::Checkbox("NonSimulate", &_Ground);
		GetTarget()->Collider3D()->SetGround(_Ground);
		
	}

	PxBounds3 bounds = actor->getWorldBounds();
	PxVec3 scale = bounds.getExtents();
	ImGui::Text("Scale: X: %f Y: %f Z: %f", scale.x, scale.y, scale.z);

	ComponentUI::RemoveComponent();

	return TRUE;
}