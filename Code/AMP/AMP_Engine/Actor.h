// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "vector"
#include "Components/Component.h"


namespace amp
{
	enum Type {
		Dynamic =	0,
		Static  =	1
	};

	class AMP_Engine;

	class Actor
	{
	public:
		Actor(Type type = Dynamic):type(type) {};
		Actor(Actor&&) = delete;
		Actor(const Actor&) = delete;

		virtual ~Actor() {};

		void SetParent(Actor* actor);

		bool HasParent();

		Actor* GetParent();

		template<typename T,typename ... Args>
		T* AddComponent(Args ... args) {
			auto* comp = new T(args ...);
			components.push_back(comp);
			return comp;
		};

		virtual void AfterSystemStartup() {};

		virtual void Update() {};

		//Root of the coordinate system is top left Just last touch is stored inside the class
		virtual void OnTouch(int32_t x, int32_t y) {};
	
		virtual void BeforeSystemShutdown() {};
	
		virtual void AfterWindowStartup() {};

		void TranslateActor(float x, float y, float z) {
			Transformation = glm::translate(Transformation, glm::vec3(x, y, z));

		}
		void RotateActor(float angle, float x, float y, float z) {
			Transformation = glm::rotate(Transformation, glm::radians(angle), glm::vec3(x, y, z));
		}
		void ScaleActor(float uniform) {
			Transformation = glm::scale(Transformation, glm::vec3(uniform, uniform, uniform));
		}

		AMP_Engine* engine = nullptr;
	private:
		//Just the initial (model)matrix is used, can not be changed during the game (better performance)
		Type type = Type::Dynamic;

		void SetEngine(AMP_Engine* engine);

		void ComponentUpdate();

		void ComponentsShutdown() {
			for (auto& comp : components) {
				delete comp;
			}
			components.clear();
		}

		void CallUpdateForComponents();

		std::vector<Component*> components;
		Actor* parent = nullptr;
		glm::mat4 Transformation = glm::mat4(1.0f);
		bool HasInitComponentUpdate = false;
		friend class AMP_Engine;
		friend class Scene;
	};
}

