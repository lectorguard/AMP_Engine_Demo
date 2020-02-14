// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "../reactphysics3d/reactphysics3d.h"
#include "memory"
#include "Static/TimeManager.h"


namespace amp
{
	class PhysicsWrapper
	{
	public:
	
		using unique_Dyn = std::unique_ptr<rp3d::DynamicsWorld>;
		using unique_Col = std::unique_ptr<rp3d::CollisionWorld>;
	
		PhysicsWrapper();
		PhysicsWrapper(const PhysicsWrapper& p) = delete;
		PhysicsWrapper(PhysicsWrapper&& p) = delete;
	
		void createDynamicWorld();
		void destroyDynamicWorld();
		void integrateDynamicPhysics();
		double factor = 0.0;
	
	private:
		unique_Dyn dynWorld = nullptr;
		int64_t previousFrameTime = 0;
		int64_t accumulator = 0;
		const float timeStep = 1.0 / 60.0;
		const int64_t timeStepInNanos = (1.0 / (float)60.0) * 1000000000;

		friend class DynamicMesh;
		friend class DynamicConcaveMesh;
	};
}

