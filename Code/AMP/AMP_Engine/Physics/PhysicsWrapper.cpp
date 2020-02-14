// Copyright 2020 Simon Keller. All Rights Reserved.

#include "pch.h"
#include "PhysicsWrapper.h"



void amp::PhysicsWrapper::integrateDynamicPhysics()
{
	if (!dynWorld.get())throw "A Dynamic World has to be created before the integration step";
	// Get the current system time 
	int64_t currentFrameTime = TIME::currentTimeInNanos();

	// Compute the time difference between the two frames 
	int64_t deltaTime = currentFrameTime - previousFrameTime;

	// Update the previous time 
	previousFrameTime = currentFrameTime;

	deltaTime = std::min(deltaTime, (int64_t)(10 * timeStepInNanos));

	// Add the time difference in the accumulator 
	accumulator += deltaTime;

	// While there is enough accumulated time to take 
	// one or several physics steps 
	int simulationCounter = 0;
	while (accumulator >= timeStepInNanos) {

		// Update the Dynamics world with a constant time step 
		dynWorld.get()->update(timeStep);

		// Decrease the accumulated time 
		accumulator -= timeStepInNanos;
		++simulationCounter;
	}

	// Compute the time interpolation factor 
	factor = accumulator / (double)timeStepInNanos;
}

amp::PhysicsWrapper::PhysicsWrapper()
{
}

void amp::PhysicsWrapper::createDynamicWorld()
{
	rp3d::Vector3 gravity(0.0, -9.81, 0.0);
	dynWorld = std::make_unique<rp3d::DynamicsWorld>(gravity);
	dynWorld.get()->setNbIterationsVelocitySolver(30);
	dynWorld.get()->setNbIterationsPositionSolver(15);
}

void amp::PhysicsWrapper::destroyDynamicWorld()
{
	dynWorld.reset(nullptr);
}
