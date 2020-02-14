// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "Components/Mesh.h"
#include "Components/DynamicMesh.h"
#include "Actor.h"
#include "AMP_Engine.h"
#include "Text.h"
#include "string"
#include "time.h"
#include "Event/event.h"
#include "Components/DynamicConcaveMesh.h"

class RigidBody : public amp::Actor
{
public:
	RigidBody(amp::Type type):Actor(type) {
		box = AddComponent<amp::Mesh>();
		boxCollision = AddComponent<amp::DynamicMesh>();
		landscapeCollision = AddComponent<amp::DynamicConcaveMesh>();
		landscape = AddComponent<amp::Mesh>();
	}
	amp::Mesh* box;
	amp::DynamicMesh* boxCollision;
	amp::Mesh* landscape;
	amp::DynamicConcaveMesh* landscapeCollision;

	virtual void AfterWindowStartup() override;

	void ResetRigidBodyTransform();

	void AfterTimerFunc();

};