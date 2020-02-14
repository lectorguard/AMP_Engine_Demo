// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "Components/Mesh.h"
#include "Actor.h"
#include "AMP_Engine.h"
#include "Components/TextRenderer.h"
#include "Text.h"
#include "string"
#include "time.h"
#include "Event/event.h"


class HelmetActor : public amp::Actor
{

public:
	HelmetActor(amp::Type type):Actor(type){
		helmet = AddComponent<amp::Mesh>();
	}
	~HelmetActor() override{};

	amp::Mesh* helmet;

	void Update() override;

	void OnTouch(int32_t x, int32_t y) override;

	void AfterWindowStartup() override;
};

