// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "../reactphysics3d/reactphysics3d.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

namespace amp{

	enum PhysicType { StaticBody, KinematicBody, DynamicBody };

	static rp3d::Transform GetReactTrans(glm::mat4 mat)
	{
		rp3d::Transform transform;
		transform.setFromOpenGL(glm::value_ptr(mat));
		return transform;
	}

	static glm::mat4 GetGLMTransform(rp3d::Transform transform)
	{
		float matrix[16];
		transform.getOpenGLMatrix(matrix);
		return glm::make_mat4(matrix);
	}
}
