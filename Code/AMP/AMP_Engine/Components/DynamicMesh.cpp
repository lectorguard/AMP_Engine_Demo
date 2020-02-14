// Copyright 2020 Simon Keller. All Rights Reserved.

#include "pch.h"
#include "DynamicMesh.h"



amp::DynamicMesh::~DynamicMesh()
{
	engine->physics.dynWorld.get()->destroyRigidBody(rigidBody);
	if (convexMeshShape)delete convexMeshShape;
	if (boxShape)delete boxShape;
	if (sphereShape) delete sphereShape;
	if (capsuleShape)delete capsuleShape;
	delete polyhedronMesh;
	delete polygonFaces;
	delete polygonVertexArray;
}

void amp::DynamicMesh::SetUpFromConvexMesh(Mesh* createdMesh,PhysicType type, float mass /*=15.0f*/)
{
	CreateRigidBody(createdMesh, type);
	MeshAttributes* meshAttr;
	if (auto result = engine->currentScene.AssetAttribMap.tryFind(createdMesh->MeshAttributesPath.getHash())) {
		meshAttr = (MeshAttributes*)*result;
	}
	else throw "Mesh has to be set up before the Dynamic Mesh";
	meshAttr->isUsedAtRuntime = true;
	int NumberOfFaces = meshAttr->originIndices.size() / meshAttr->originIndicesPerFace;
	auto* polygonFaces = new rp3d::PolygonVertexArray::PolygonFace[NumberOfFaces];
	auto* faces = polygonFaces;
	for (int f = 0; f < NumberOfFaces; f++) {

		// First vertex of the face in the indices array 
		faces->indexBase = f * meshAttr->originIndicesPerFace;

		// Number of polygonVertexArray in the face 
		faces->nbVertices = meshAttr->originIndicesPerFace;

		faces++;
	}
	int NumberOfVertices = meshAttr->originVertices.size() / 3;

	// Create the polygon vertex array 
	polygonVertexArray = new rp3d::PolygonVertexArray(NumberOfVertices, meshAttr->originVertices.data(), 3 * sizeof(float),
		meshAttr->originIndices.data(), sizeof(int), NumberOfFaces, polygonFaces,
		rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
		rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	// Create the polyhedronMesh mesh 
	polyhedronMesh = new rp3d::PolyhedronMesh(polygonVertexArray);

	// Create the convex mesh collision shape 
	convexMeshShape = new rp3d::ConvexMeshShape(polyhedronMesh);

	rigidBody->addCollisionShape(convexMeshShape, rp3d::Transform::identity(), rp3d::decimal(mass));

	previousTransform = rp3d::Transform::identity();
}

void amp::DynamicMesh::CreateRigidBody(Mesh* createdMesh, PhysicType type)
{
	if (!createdMesh)throw "Mesh doesnt exist anymore";
	connectedMesh = createdMesh;
	if (isSetUp)throw "You can setup a dynamic body just once";
	isSetUp = true;
	rigidBody = engine->physics.dynWorld.get()->createRigidBody(GetReactTrans(createdMesh->Transform));
	rigidBody->setType(rp3d::BodyType(type));
}

void amp::DynamicMesh::SetUpBox(Mesh* fittingMesh, PhysicType type, glm::vec3 halfExtents, float mass /*= 15.0f*/)
{
	CreateRigidBody(fittingMesh, type);
	float* vec = glm::value_ptr(halfExtents);
	boxShape = new rp3d::BoxShape(rp3d::Vector3(vec[0],vec[1],vec[2]));
	rigidBody->addCollisionShape(boxShape, rp3d::Transform::identity(), rp3d::decimal(mass));
	previousTransform = rp3d::Transform::identity();
}

void amp::DynamicMesh::SetUpSphere(Mesh* fittingMesh, PhysicType type, float radius, float mass /*= 15.0f*/)
{
	CreateRigidBody(fittingMesh, type);
	sphereShape = new rp3d::SphereShape(radius);
	rigidBody->addCollisionShape(sphereShape, rp3d::Transform::identity(), rp3d::decimal(mass));
	previousTransform = rp3d::Transform::identity();
}

void amp::DynamicMesh::SetUpCapsule(Mesh* fittingMesh, PhysicType type, float radius, float height, float mass /*= 15.0f*/)
{
	CreateRigidBody(fittingMesh, type);
	capsuleShape = new rp3d::CapsuleShape(radius, height);
	rigidBody->addCollisionShape(capsuleShape, rp3d::Transform::identity(), rp3d::decimal(mass));
	previousTransform = rp3d::Transform::identity();
}

rp3d::Material& amp::DynamicMesh::getPhysicMaterial()
{
	return rigidBody->getMaterial();
}


void amp::DynamicMesh::setGravity(bool isGravity)
{
	rigidBody->enableGravity(isGravity);
}

bool amp::DynamicMesh::isGravity()
{
	return rigidBody->isGravityEnabled();
}

void amp::DynamicMesh::setActive(bool isActive)
{
	rigidBody->setIsActive(isActive);
}

bool amp::DynamicMesh::isActive()
{
	return rigidBody->isActive();
}

void amp::DynamicMesh::applyForceToCenter(rp3d::Vector3 force)
{
	rigidBody->applyForceToCenterOfMass(force);
}

void amp::DynamicMesh::applyForce(rp3d::Vector3 force, rp3d::Vector3 point)
{
	rigidBody->applyForce(force, point);
}

void amp::DynamicMesh::applyTorque(rp3d::Vector3 torque)
{
	rigidBody->applyTorque(torque);
}

glm::mat4 amp::DynamicMesh::getTransform()
{
	return GetGLMTransform(rigidBody->getTransform());
}

void amp::DynamicMesh::setTransform(glm::mat4 transform, bool resetLinearVelocity, bool resetAngularVelocity)
{
	rigidBody->setTransform(GetReactTrans(transform));
	if(resetLinearVelocity)rigidBody->setLinearVelocity(rp3d::Vector3(0, 0, 0));
	if(resetAngularVelocity)rigidBody->setAngularVelocity(rp3d::Vector3(0, 0, 0));
}

void amp::DynamicMesh::update()
{
	if (!connectedMesh)throw "connected Mesh is invalid, maybe you forgot to init this component";
	if (!engine)throw "engine was not initialised";
	rp3d::Transform currTransform = rigidBody->getTransform();
 
 	// Compute the interpolated transform of the rigid body 
 	rp3d::Transform interpolatedTransform = rp3d::Transform::interpolateTransforms(previousTransform, currTransform, engine->physics.factor);
	connectedMesh->Transform = GetGLMTransform(interpolatedTransform);

 	// Update the previous transform 
 	previousTransform = currTransform;
}
