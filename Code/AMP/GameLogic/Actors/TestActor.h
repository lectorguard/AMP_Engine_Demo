// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "Actor.h"
#include "AMP_Engine.h"
#include "Components/TextRenderer.h"




class TestActor : public amp::Actor
{
public:
	 amp::TextRenderer* rend;
	 TestActor(amp::Type type) :Actor(type) {
		rend = AddComponent<amp::TextRenderer>();
	 }

	 void Update() override;
	
	 void OnTouch(int32_t x, int32_t y) override;

	 void AfterWindowStartup() override;
};

