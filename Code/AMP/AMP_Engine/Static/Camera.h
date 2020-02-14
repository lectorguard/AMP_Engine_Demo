// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtx/quaternion.hpp"
#include "Static/TimeManager.h"

struct Camera
{
	static glm::mat4 getView() {
		return view;
	}

	static glm::mat4 getProjection() {
		return projection;
	}

	static void setView(glm::mat4 newModel) {
		if (TIME::currentTimeInNanos() == lastTimeModel)throw "You changed the Model Matrix two times in one Frame, thats not allowed";
		view = newModel;
		lastTimeModel = TIME::currentTimeInNanos();
	}

	static void setProjection(glm::mat4 newProjection) {
		if (TIME::currentTimeInNanos() == lastTimeProjection)throw "You changed the Model Matrix two times in one Frame, thats not allowed";
		projection = newProjection;
		lastTimeProjection = TIME::currentTimeInNanos();
	}

private:
	//default values are inside the cpp files
	static glm::mat4 view;
	static glm::mat4 projection;
	static double lastTimeModel;
	static double lastTimeProjection;
	friend class AMP_Engine;
};