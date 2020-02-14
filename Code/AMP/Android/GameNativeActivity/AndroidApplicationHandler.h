// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "AMP_Engine.h"
#include <malloc.h>


namespace Android
{
	struct saved_state {
		float angle;
		int32_t x = -1;
		int32_t y = -1;
	};
	
	
	class AndroidApplicationHandler
	{
	public:
		AndroidApplicationHandler();

		AndroidApplicationHandler(const AndroidApplicationHandler&) = delete;
		AndroidApplicationHandler(AndroidApplicationHandler&&) = delete;

		bool updateHandlerAndroid(amp::AndroidStatus* status);
		void InitializeAndroidHandler(struct android_app* state);
	private:
		static void android_handle_cmd(struct android_app* app, int32_t cmd);
		static void Save(AndroidApplicationHandler* apkHandler);
		static void PrepareShutdownAPK(AndroidApplicationHandler* apkHandler);
		static void TermWindow(AndroidApplicationHandler* apkHandler);
		static void HandleLostFocus(AndroidApplicationHandler* apkHandler);
		static void InitWindow(AndroidApplicationHandler* apkHandler);
		static void PrepareInitAPK(AndroidApplicationHandler* apkHandler);
		static void RestartSensorEventQueue(AndroidApplicationHandler* apkHandler);
		static int32_t android_handle_input(struct android_app* app, AInputEvent* event);

		struct android_app* app;
		ASensorManager* sensorManager;
		const ASensor* accelerometerSensor;
		ASensorEventQueue* sensorEventQueue;
		amp::CommandsAndroid currentCommand = amp::NO_CMD;
		//updating actors and components
		int animating;
		//when focus is lost a clean shutdown is executed followed by an init
		//When focus is lost no graphic memory is accessible for the apk (=> Shutdown)
		int ProcessShutdown = 0;
		struct saved_state saveState;
	};
}



