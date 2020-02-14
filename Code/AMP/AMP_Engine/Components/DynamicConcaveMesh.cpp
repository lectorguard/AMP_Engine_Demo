// Copyright 2020 Simon Keller. All Rights Reserved.

#include "pch.h"
#include "DynamicConcaveMesh.h"

amp::DynamicConcaveMesh::~DynamicConcaveMesh()
{
	engine->physics.dynWorld.get()->destroyRigidBody(rigidbody);
	delete concaveMesh;
	delete triangleMesh;
	delete triangleArray;
}

void amp::DynamicConcaveMesh::SetUpFromMesh(Mesh* createdMesh, PhysicType type)
{
	if (!createdMesh)throw "Mesh doesnt exist anymore";
	connectedMesh = createdMesh;
	MeshAttributes* meshAttr;
	if (auto result = engine->currentScene.AssetAttribMap.tryFind(createdMesh->MeshAttributesPath.getHash())) {
		meshAttr = (MeshAttributes*)*result;
	}
	else throw "Mesh has to be set up before the Dynamic Mesh";
	meshAttr->isUsedAtRuntime = true;
	int NumberOfVertices = meshAttr->positions.size() / 3;
	int NumberOfTriangles = meshAttr->indices.size() / 3;
	triangleArray = new rp3d::TriangleVertexArray(NumberOfVertices, meshAttr->positions.data(), 3 * sizeof(float),
		NumberOfTriangles, meshAttr->indices.data(), 3 * sizeof(int),
		rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
		rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
	triangleMesh = new rp3d::TriangleMesh();
	triangleMesh->addSubpart(triangleArray);
	concaveMesh = new rp3d::ConcaveMeshShape(triangleMesh);
	rigidbody = engine->physics.dynWorld.get()->createRigidBody(GetReactTrans(createdMesh->Transform));
	rigidbody->addCollisionShape(concaveMesh, rp3d::Transform::identity(), rp3d::decimal(30.0));
	rigidbody->setType(rp3d::BodyType(type));
	prevTrans = GetReactTrans(createdMesh->Transform);
}

rp3d::Material& amp::DynamicConcaveMesh::getPhysicMaterial()
{
	return rigidbody->getMaterial();
}

void amp::DynamicConcaveMesh::setGravity(bool isGravity)
{
	rigidbody->enableGravity(isGravity);
}

bool amp::DynamicConcaveMesh::isGravity()
{
	return rigidbody->isGravityEnabled();
}

void amp::DynamicConcaveMesh::setActive(bool isActive)
{
	rigidbody->setIsActive(isActive);
}

bool amp::DynamicConcaveMesh::isActive()
{
	return rigidbody->isActive();
}

void amp::DynamicConcaveMesh::applyForceToCenter(rp3d::Vector3 force)
{
	rigidbody->applyForceToCenterOfMass(force);
}

void amp::DynamicConcaveMesh::applyForce(rp3d::Vector3 force, rp3d::Vector3 point)
{
	rigidbody->applyForce(force, point);
}

void amp::DynamicConcaveMesh::applyTorque(rp3d::Vector3 torque)
{
	rigidbody->applyTorque(torque);
}

void amp::DynamicConcaveMesh::setTransform(glm::mat4 transform)
{
	rigidbody->setTransform(GetReactTrans(transform));
}

glm::mat4 amp::DynamicConcaveMesh::getTransform()
{
	return GetGLMTransform(rigidbody->getTransform());
}

void amp::DynamicConcaveMesh::update()
{
	if (!connectedMesh)throw "connected Mesh is invalid, maybe you forgot to init this component";
	if (!engine)throw "engine was not initialised";

	//update mesh Location
	rp3d::Transform currTransform = rigidbody->getTransform();
	// Compute the interpolated transform of the rigid body 
	rp3d::Transform interpolatedTransform = rp3d::Transform::interpolateTransforms(prevTrans, currTransform, engine->physics.factor);
	connectedMesh->Transform = GetGLMTransform(interpolatedTransform);
	// Update the previous transform 
	prevTrans = currTransform;
}
