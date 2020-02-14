// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "Scene.h"
#include "AMP_Engine.h"
#include "Static/Camera.h"
#include "Graphics/CubeMap.h"
#include "Actors/HelmetActor.h"
#include "Actors/TestActor.h"
#include "Actors/RigidBody.h"


class DemoScene : public amp::Scene
{
public:
	HelmetActor* helmet;
	TestActor* testActor;
	RigidBody* rb;
	amp::CubeMap* cubeMap;
public:
	DemoScene(amp::AMP_Engine* engine) :amp::Scene(engine) {		
	}

protected:
	void load() override
	{
		Camera::setView(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-20.0f, -90.0f)));
		Camera::setView(glm::rotate(Camera::getView(), glm::radians(45.0f), glm::vec3(0.8, 1, 0)));
		cubeMap = CreateActor<amp::CubeMap>(amp::Type::Static);
		cubeMap->createCubeMap(TEXT("SkyBox/forward.png"), TEXT("SkyBox/backward.png"),
			TEXT("SkyBox/left.png"), TEXT("SkyBox/right.png"),
			TEXT("SkyBox/top.png"), TEXT("SkyBox/bottom.png"));
		testActor = CreateUIActor<TestActor>(amp::Type::Dynamic);
		testActor->TranslateActor(0, 0, -10);
		helmet = CreateActor<HelmetActor>(amp::Type::Dynamic);
 		helmet->TranslateActor(10, -13, -10);
 		helmet->SetParent(testActor);
		rb = CreateActor<RigidBody>(amp::Type::Dynamic);
	}
};

