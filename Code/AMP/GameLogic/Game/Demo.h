// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "AMP_Engine.h"
#include "android/asset_manager.h"
#include "string"
#include "memory"
#include "Scenes/DemoScene.h"
#include "Static/Camera.h"


class Demo : public amp::AMP_Engine
{
public:

	std::unique_ptr<DemoScene> scene1;
	std::unique_ptr<DemoScene> scene2;
	Demo(AAssetManager * AssetManager,std::string InternalDataPath):AMP_Engine(AssetManager,InternalDataPath) {
		scene1 = std::make_unique<DemoScene>(this);
		scene2 = std::make_unique<DemoScene>(this);
	};
	
	
protected:
	void update() override;


	void BeforeSystemShutdown() override;


	void AfterWindowStartup() override;
private:
	int FrameCounter = 0;

};

