// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "functional"
#include "assert.h"
#include "Graphics/Context.h"
#include "android/asset_manager.h"
#include "../AssetLoader/MeshLoaderFromObj.h"
#include "Graphics/FrameBuffer.h"
#include "string"
#include "Graphics/Shader.h"
#include "Actor.h"
#include "memory"
#include "Memory/AMP_Memory.h"
#include "Memory/CurrentSceneContainer.h"
#include "../AssetLoader/Attributes.h"
#include "Event/EventSystem.h"
#include "Physics/PhysicsWrapper.h"

namespace amp {
	

	enum CommandsAndroid {
		NO_CMD					=	0,
		APP_CMD_INIT_WINDOW		=	1,
		APP_CMD_TERM_WINDOW		=	2,
		APP_CMD_GAINED_FOCUS	=	3,
		APP_CMD_LOST_FOCUS		=	4
	};

	struct AndroidStatus {
		CommandsAndroid commands = NO_CMD;
		ANativeWindow* window = nullptr;
		bool touchEvent = false;
		int32_t TouchX;
		int32_t TouchY;
		int animating;
		int ProcessShutdown = 0;
	};

	class AMP_Engine
	{
		using FuncHandle_t = std::function<void(Actor* actor)>;
		using VectorFunctionHandle_t = std::vector<std::function<void()>>;
	public:
		AMP_Engine(AAssetManager* AssetManager,std::string InternalDataPath) {
			ampShader.setAssetManager(AssetManager);
			this->assetManager = AssetManager;
			meshLoader.setAssetManager(AssetManager);
			// TO DO: set internal data path in File Manager, read/write save files
		}
	    ~AMP_Engine();
		AMP_Engine(const AMP_Engine&) = delete;
		AMP_Engine(AMP_Engine&&) = delete;

		void run(std::function<bool(AndroidStatus*)> AndroidStatusInput);

		double getFrameTime();

		double getCalculationTime();

		void addTimerFuction(TimeEvent timeEvent);

		void removeLoopedTimerFunction(TimeEvent& timeEvent);

		Context ampContext;
		Shader ampShader;
		AAssetManager* assetManager;
		MeshLoaderFromObj meshLoader;
		EventSystem events;
		FrameBuffer sceneBuffer;
		FrameBuffer UIBuffer;
		PhysicsWrapper physics;
		VectorFunctionHandle_t postSceneUpdate;

	protected:
		//Compile no shader code here !!!! Take instead AfterWindowStartup to do so
		virtual void AfterSystemStartup() {};

		virtual void AfterWindowStartup() {};

		virtual void update() {};
		
		//Root of the coordinate system is top left Just last touch is stored inside the class
		virtual void OnTouch(int32_t x, int32_t y) {};

		virtual void BeforeSystemShutdown() {};

	private:
		void SystemStartupCallback();
		void AfterWindowStartupCallback();
		void UpdateCallback();
		void PostSceneUpdateCallback();
		void publishUIActorComponentsUpdate();
		void publishSceneActorComponentsUpdate();
		void OnTouchCallback(int32_t x, int32_t y);
		void BeforeSystemShutdownCallback();
		void publishActorEvent(FuncHandle_t function);
		void publishUIEvent(FuncHandle_t function);
		void PrepareShutdown();
		void InitSystems();
		void PublishTouchEvents(AndroidStatus& status);
		void GameUpdate();
		void Shutdown();

		CurrentSceneContainer currentScene;

		double calculationTime = 0.0;
		double frameTime = 0.0;
		int64_t startTime = 0;
		bool isRuntime = false;
		bool hasDisplay = false;
		int32_t TouchX;
		int32_t TouchY;
		bool animating = true;

		friend class Scene;
		friend class Mesh;
		friend class TextRenderer;
		friend class DynamicMesh;
		friend class DynamicConcaveMesh;
		friend class CubeMap;
	};
}
