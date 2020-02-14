// Copyright 2020 Simon Keller. All Rights Reserved.

#include "TestActor.h"
#include "Static/Camera.h"


void TestActor::Update()
{
	RotateActor(1, 0, 1, 0);
	rend->renderText(std::to_string(1 / engine->getFrameTime()), 110, 1200, 66, 0.001f);
}

void TestActor::OnTouch(int32_t x, int32_t y)
{
	RotateActor(1, 0, 1, 0);
}

void TestActor::AfterWindowStartup()
{
	rend->setColor(1.0f, 0.0f, 0.0f);
	rend->setAnimation(true);
	rend->setUpText(TEXT("Font/default.bmp"), TEXT("Shader/FontShader.glsl"));
	rend->renderText("FPS:", 200, 1300, 60);
}
