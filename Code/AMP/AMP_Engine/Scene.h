// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "AMP_Engine.h"
#include "Memory/AMP_Memory.h"
#include "memory"
#include "cassert"
#include "Actor.h"

namespace amp
{
	class Scene
	{
	public:
		Scene(AMP_Engine* engine) {
			assert(engine != nullptr && "engine not initialized");
			this->engine = engine;
		}
		
		void loadScene(bool unloadAssetAttributes = true) {
			if (engine->currentScene.IsActiveScene)throw "You can just have one active Scene at a time, unload the scene before loading a new one";
			else 
			{
				engine->currentScene.IsActiveScene = true;
				load();
				if (unloadAssetAttributes)engine->currentScene.removeUnusedRuntimeMapElements();
			}
		}
		
		void unloadScene() {
			engine->BeforeSystemShutdownCallback();
			engine->currentScene.clear(true);
			engine->events.clear();
		}
	
	protected:
		virtual void load(){};

		//These actors should just be used inside your scene otherwise there is a memory leak
		template<typename T, typename ... Args>
		T* CreateActor(Args ... args) {
			engine->currentScene.CurrentSceneActorArray.add(std::make_unique<T>(std::forward<Args>(args)...));
			auto* s =actorAt(engine->currentScene.CurrentSceneActorArray.count() - 1);
			SetUpActor(s);
			return static_cast<T*> (s);
		}

		//These actors should just be used inside your scene otherwise there is a memory leak
		template<typename T, typename ... Args>
		T* CreateUIActor(Args ... args) {
			engine->currentScene.CurrentSceneUIArray.add(std::make_unique<T>(std::forward<Args>(args) ...));
			auto* s = UIactorAt(engine->currentScene.CurrentSceneUIArray.count() - 1);
			SetUpActor(s);
			return static_cast<T*> (s);
		}

		void SetUpActor(Actor* s)
		{
			s->SetEngine(engine);
			for (auto& comp : s->components)
			{
				comp->setEngine(engine);
			}
			if (engine->isRuntime) {
				s->AfterSystemStartup();
				s->AfterWindowStartup();
			}
		}

	private:
		Actor* actorAt(int i) {
			return engine->currentScene.CurrentSceneActorArray[i].get();
		}

		Actor* UIactorAt(int i) {
			return engine->currentScene.CurrentSceneUIArray[i].get();
		}
		AMP_Engine* engine = nullptr;
	};
}

