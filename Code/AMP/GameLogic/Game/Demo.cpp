// Copyright 2020 Simon Keller. All Rights Reserved.

#include "Demo.h"

void Demo::AfterWindowStartup()
{
	float aspect = ampContext.getWidth() / (float)ampContext.getHeight(); //Samsung tablet 1920/1200
	Camera::setProjection(glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f));
	scene1.get()->loadScene(false);
}

void Demo::update()
{
	FrameCounter++;
	if(FrameCounter==700){
		scene1.get()->unloadScene();
	}

	if (FrameCounter == 750) {
		scene2.get()->loadScene();
	}

}

void Demo::BeforeSystemShutdown()
{
	scene2.get()->unloadScene();
}


