// Copyright 2020 Simon Keller. All Rights Reserved.

#include "pch.h"
#include "RigidBody.h"


void RigidBody::AfterWindowStartup()
{
	box->Mesh_SetUpGL(TEXT("Shader/MeshShader.glsl"), TEXT("3DModels/box.obj"), TEXT("3DModels/box.mtl"), TEXT("Textures/wood.jpg"));
	box->translate(0, 40, 0);
	box->rotate(180, 1, 1, 0);
	boxCollision->SetUpFromConvexMesh(box, amp::PhysicType::DynamicBody);
 	landscape->Mesh_SetUpGL(TEXT("Shader/MeshShader.glsl"), TEXT("3DModels/landscape.obj"), TEXT("3DModels/landscape.mtl"), TEXT("Textures/brick.png"));
 	landscapeCollision->SetUpFromMesh(landscape, amp::PhysicType::StaticBody);
	landscapeCollision->setGravity(false);
	//reset box
	amp::TimeEvent timeEv;
	timeEv.init<RigidBody>(6.0f, true, &RigidBody::AfterTimerFunc, this);
	engine->addTimerFuction(timeEv);
	engine->events.subscribeEvent<RigidBody>(TEXT("ResetRigidBodies"), &RigidBody::ResetRigidBodyTransform, this);
}

void RigidBody::ResetRigidBodyTransform()
{
	glm::mat4 origin = glm::identity<glm::mat4>();
	origin = glm::translate(origin, glm::vec3(0, 40, 0));
	boxCollision->setTransform(origin,true,false);
}

void RigidBody::AfterTimerFunc()
{
	engine->events.publishEvent(TEXT("ResetRigidBodies"));
}




