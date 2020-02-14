// Copyright 2020 Simon Keller. All Rights Reserved.

#include "AMP_Engine.h"
#include <android\native_window.h>



amp::AMP_Engine::~AMP_Engine()
{
}



void amp::AMP_Engine::run(std::function<bool(AndroidStatus*)> AndroidStatusInput)
{
	AfterSystemStartup();
	SystemStartupCallback();
	AndroidStatus status;
	isRuntime = true;
	while (AndroidStatusInput(&status))
	{
		startTime = TIME::currentTimeInNanos();
		if (status.ProcessShutdown) {
			status.ProcessShutdown = 0;
			PrepareShutdown();
		}
		if (status.commands == APP_CMD_INIT_WINDOW) {
			ampContext.initDisplay(status.window);
			InitSystems();
		}
		if (status.commands == APP_CMD_LOST_FOCUS) {
			GameUpdate();
			animating = false;
		}
		if (status.touchEvent && animating) {
			//Always last touch is stored
			PublishTouchEvents(status);
		}
		animating = status.animating;	
		if (animating && hasDisplay) {
			GameUpdate();
		}
		frameTime = TIME::NanosToSeconds(TIME::currentTimeInNanos() - startTime);
	}	
	Shutdown();
}

void amp::AMP_Engine::Shutdown()
{
	BeforeSystemShutdownCallback();
	currentScene.clear(false);
	BeforeSystemShutdown();
	physics.destroyDynamicWorld();
	ampContext.termDisplay();
}

void amp::AMP_Engine::GameUpdate()
{
	physics.integrateDynamicPhysics();
	UpdateCallback();
	sceneBuffer.clear(true);
	publishSceneActorComponentsUpdate();
	PostSceneUpdateCallback();
	UIBuffer.clear();
	publishUIActorComponentsUpdate();
	sceneBuffer.drawFrameBufferContent();
	UIBuffer.drawFrameBufferContent();
	update();
	// performance measurement
	calculationTime = TIME::NanosToSeconds(TIME::currentTimeInNanos() - startTime);
	ampContext.SwapBuffers();
}

void amp::AMP_Engine::PublishTouchEvents(AndroidStatus& status)
{
	TouchX = status.TouchX;
	TouchY = status.TouchY;
	OnTouchCallback(status.TouchX, status.TouchY);
	OnTouch(status.TouchX, status.TouchY);
}

void amp::AMP_Engine::InitSystems()
{
	this->hasDisplay = true;
	//createPhysics
	physics.createDynamicWorld();
	AfterWindowStartupCallback();
	AfterWindowStartup();
	sceneBuffer.enable(this);
	UIBuffer.enable(this);
}

void amp::AMP_Engine::PrepareShutdown()
{
	BeforeSystemShutdownCallback();
	currentScene.clear(false);
	BeforeSystemShutdown();
	ampContext.termDisplay();
	hasDisplay = false;
}

double amp::AMP_Engine::getFrameTime()
{
	if (!frameTime)return 1.0;
	return frameTime;
}

double amp::AMP_Engine::getCalculationTime()
{
	if (!calculationTime)return 1.0;
	return calculationTime;
}

void amp::AMP_Engine::addTimerFuction(TimeEvent timeEvent)
{
	events.addTimerFuction(timeEvent);
}

void amp::AMP_Engine::removeLoopedTimerFunction(TimeEvent& timeEvent)
{
	events.removeLoopedTimerFunction(timeEvent);
}

void amp::AMP_Engine::SystemStartupCallback()
{
	publishActorEvent([](Actor* a) {a->AfterSystemStartup(); });
	publishUIEvent([](Actor* a) {a->AfterSystemStartup(); });
}


void amp::AMP_Engine::AfterWindowStartupCallback()
{
	publishActorEvent([](Actor* a) {a->AfterWindowStartup(); });
	publishUIEvent([](Actor* a) {a->AfterWindowStartup(); });
}

void amp::AMP_Engine::UpdateCallback()
{
	events.publishTimeEvent();
	publishActorEvent([](Actor* a) {a->Update(); });
	publishUIEvent([](Actor* a) {a->Update(); });
}

void amp::AMP_Engine::PostSceneUpdateCallback()
{
	for (auto& callback : postSceneUpdate) {
		callback();
	}
}

void amp::AMP_Engine::publishUIActorComponentsUpdate()
{
	publishUIEvent([](Actor* a) {a->ComponentUpdate(); });
}

void amp::AMP_Engine::publishSceneActorComponentsUpdate()
{
	publishActorEvent([](Actor* a) {a->ComponentUpdate(); });
}

void amp::AMP_Engine::OnTouchCallback(int32_t x, int32_t y)
{
	publishActorEvent([x, y](Actor* a) {a->OnTouch(x, y); });
	publishUIEvent([x, y](Actor* a) {a->OnTouch(x, y); });
}

void amp::AMP_Engine::BeforeSystemShutdownCallback()
{
	publishActorEvent([](Actor* a) {a->ComponentsShutdown(); a->BeforeSystemShutdown();});
	publishUIEvent([](Actor* a) {a->ComponentsShutdown(); a->BeforeSystemShutdown(); });
	postSceneUpdate.clear();
}

void amp::AMP_Engine::publishActorEvent(FuncHandle_t function)
{
	for (int k = 0; k < currentScene.CurrentSceneActorArray.count(); k++) {
		auto* ref = currentScene.CurrentSceneActorArray[k].get();
		function(ref);
	}
}

void amp::AMP_Engine::publishUIEvent(FuncHandle_t function)
{
	for (int k = 0; k < currentScene.CurrentSceneUIArray.count(); k++) {
		auto* ref = currentScene.CurrentSceneUIArray[k].get();
		function(ref);
	}
}






