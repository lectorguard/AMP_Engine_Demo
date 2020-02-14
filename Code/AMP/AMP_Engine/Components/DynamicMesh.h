// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "Components/Component.h"
#include "Components/Mesh.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "memory"
#include "../reactphysics3d/reactphysics3d.h"
#include "Physics/PhysicHelper.h"

namespace amp{

	class DynamicMesh : public Component
	{
	public:
		DynamicMesh() {};
		~DynamicMesh();
		DynamicMesh(const DynamicMesh&) = delete;
		DynamicMesh(DynamicMesh&&) = delete;

		///Mesh has to be already set up
		///Move the dynamic component when you want to move the mesh
		void SetUpFromConvexMesh(Mesh* createdMesh,PhysicType type, float mass =15.0f);

		//Mesh has to be already set up, obj must contain polygonVertexArray and polygonFaces
		void SetUpBox(Mesh* fittingMesh, PhysicType type,glm::vec3 halfExtents, float mass = 15.0f);
		void SetUpSphere(Mesh* fittingMesh, PhysicType type, float radius, float mass = 15.0f);
		void SetUpCapsule(Mesh* fittingMesh, PhysicType type, float radius, float height, float mass = 15.0f);

		rp3d::Material& getPhysicMaterial();

		void setGravity(bool isGravity);
		void setActive(bool isActive);
		bool isGravity();
		bool isActive();

		void applyForceToCenter(rp3d::Vector3 force);

		void applyForce(rp3d::Vector3 force, rp3d::Vector3 point);

		void applyTorque(rp3d::Vector3 torque);

		glm::mat4 getTransform();

		void setTransform(glm::mat4 transform, bool resetLinearVelocity = true, bool resetAngularVelocity = true);

	protected:
		virtual void update() override;
	private:
		void CreateRigidBody(Mesh* createdMesh, PhysicType type);
		rp3d::RigidBody* rigidBody = nullptr;
		//have to be self organized
		rp3d::PolygonVertexArray* polygonVertexArray = nullptr;
		rp3d::PolygonVertexArray::PolygonFace* polygonFaces = nullptr;
		rp3d::PolyhedronMesh* polyhedronMesh = nullptr;
		rp3d::ConvexMeshShape* convexMeshShape = nullptr;
		rp3d::BoxShape* boxShape = nullptr;
		rp3d::SphereShape* sphereShape = nullptr;
		rp3d::CapsuleShape* capsuleShape = nullptr;
		Mesh* connectedMesh = nullptr;
		rp3d::Transform previousTransform;
		bool isSetUp = false;
	};
}



