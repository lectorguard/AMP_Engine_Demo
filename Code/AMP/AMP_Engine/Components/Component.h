// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtx/quaternion.hpp"

namespace amp
{
	class AMP_Engine;
	class Component
	{
	public:
	
		Component(){};
		virtual ~Component(){};

		Component(Component&&) = delete;
		Component(const Component&) = delete;

		void translate(float x, float y, float z) {
			Transform = glm::translate(Transform, glm::vec3(x,y,z));
		}
		void rotate(float angle,float x, float y, float z) {
			Transform = glm::rotate(Transform, glm::radians(angle), glm::vec3(x, y, z));
		}
		void scale(float uniform) {
			Transform = glm::scale(Transform, glm::vec3(uniform, uniform, uniform));
		}
	protected:
		glm::mat4 Transform = glm::mat4(1.0f);
		glm::mat4 AppliedTransform = glm::mat4(1.0f);
		virtual void update() = 0;
		amp::AMP_Engine* engine = nullptr;
	private:
		void applyTransform(glm::mat4 actorEntityTransform) {
			AppliedTransform = actorEntityTransform * Transform;
		};

		void setEngine(amp::AMP_Engine* engine) {
			this->engine = engine;
		}
		friend class Scene;
		friend class Actor;
	};
}


