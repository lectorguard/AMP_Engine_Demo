// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "memory"
#include "AMP_Memory.h"
#include "AMP_HashMap.h"
#include "../AssetLoader/Attributes.h"
#include "Actor.h"


namespace amp{

	struct CurrentSceneContainer
	{
		using ActorContainer_t = LinearArray<std::unique_ptr<Actor>, 128>;
		using UIContainer_t = LinearArray<std::unique_ptr<Actor>, 32>;

		void clear(bool IsCleanUp) {
			CurrentSceneActorArray.clear();
			CurrentSceneUIArray.clear();
			IsActiveScene = false;
			if (IsCleanUp)removeRuntimeMapElements();
			else clearMap();
		}

		void clearMap(){
			for (std::pair<size_t, Attributes*> element : AssetAttribMap) {
				delete element.second;
			}
			AssetAttribMap.clear();
		}

		void removeRuntimeMapElements() {
			cleanUpMapOnRuntimeUsage(false);
		}

		void removeUnusedRuntimeMapElements() {
			cleanUpMapOnRuntimeUsage(true);
		}

		HashMap<size_t, Attributes*> AssetAttribMap;
	private:
		void cleanUpMapOnRuntimeUsage(bool ConditionInverted) {
			auto iter = AssetAttribMap.begin();
			auto endIter = AssetAttribMap.end();
			for (; iter != endIter;) {
				if (ConditionInverted) {
					if (!iter->second->isUsedAtRuntime) {
						delete iter->second;
						AssetAttribMap.erase(iter++);
					}
					else ++iter;
				}
				else
				{
					if (iter->second->isUsedAtRuntime) {
						delete iter->second;
						AssetAttribMap.erase(iter++);
					} 
					else ++iter;
				}
			}
		}

		ActorContainer_t CurrentSceneActorArray;
		UIContainer_t CurrentSceneUIArray;
		bool IsActiveScene = false;
		friend class AMP_Engine;
		friend class Scene;
	};
}
