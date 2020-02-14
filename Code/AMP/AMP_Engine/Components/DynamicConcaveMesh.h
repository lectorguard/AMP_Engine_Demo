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

namespace amp
{
	
	class DynamicConcaveMesh : public Component
	{
	public:
		DynamicConcaveMesh() {};
	    ~DynamicConcaveMesh();
		DynamicConcaveMesh(const DynamicConcaveMesh&) = delete;
		DynamicConcaveMesh(DynamicConcaveMesh&&) = delete;
	
		///Mesh has to be already set up
		///Move the dynamic component when you want to move the mesh
		void SetUpFromMesh(Mesh * createdMesh, PhysicType type);

		rp3d::Material& getPhysicMaterial();

		void setGravity(bool isGravity);

		bool isGravity();

		void setActive(bool isActive);

		bool isActive();

		void applyForceToCenter(rp3d::Vector3 force);

		void applyForce(rp3d::Vector3 force, rp3d::Vector3 point);

		void applyTorque(rp3d::Vector3 torque);

		void setTransform(glm::mat4 transform);

		glm::mat4 getTransform();
	
	protected:
		virtual void update() override;

	private:
		Mesh* connectedMesh;
		rp3d::TriangleVertexArray* triangleArray;
		rp3d::TriangleMesh* triangleMesh;
		rp3d::ConcaveMeshShape* concaveMesh;
		rp3d::RigidBody* rigidbody;
		rp3d::Transform prevTrans = rp3d::Transform::identity();

	};
}

