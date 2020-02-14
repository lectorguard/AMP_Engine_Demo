/*
* Copyright (C) 2010 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include <malloc.h>
#include "Game/Demo.h"
#include "AndroidApplicationHandler.h"
#include "functional"
#include "AMP_Engine.h"



void android_main(struct android_app* state) {
	Demo game = Demo(state->activity->assetManager,state->activity->internalDataPath);
	Android::AndroidApplicationHandler AndroidHandler;
	AndroidHandler.InitializeAndroidHandler(state);
	game.run([&AndroidHandler](amp::AndroidStatus* status){return AndroidHandler.updateHandlerAndroid(status);});
}
