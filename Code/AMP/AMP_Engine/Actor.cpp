// Copyright 2020 Simon Keller. All Rights Reserved.

#include "pch.h"
#include "Actor.h"

void amp::Actor::SetParent(Actor* actor)
{
	parent = actor;
}

bool amp::Actor::HasParent()
{
	return parent!=nullptr;
}

amp::Actor* amp::Actor::GetParent()
{
	return parent;
}

void amp::Actor::SetEngine(AMP_Engine* engine)
{
	assert(engine);
	this->engine = engine;
}

void amp::Actor::ComponentUpdate()
{
	if (type && HasInitComponentUpdate){
		CallUpdateForComponents();
		return;
	}
	if (!HasParent()) {
		for (auto& comp : components) {
			comp->applyTransform(Transformation);
		}
	}
	else {
		std::vector<glm::mat4> matrices;
		auto* parent = this;
		while (parent->HasParent()) {
			matrices.push_back(parent->GetParent()->Transformation);
			parent = parent->GetParent();
		}
		glm::mat4 currentTransformation = glm::mat4(1.0f);
		for (std::vector<glm::mat4>::reverse_iterator i = matrices.rbegin(); i != matrices.rend(); ++i) {
			currentTransformation = currentTransformation * (*i);
		}
		for (auto& comp : components) {
			comp->applyTransform(currentTransformation*Transformation);
		}
	}
	CallUpdateForComponents();
	HasInitComponentUpdate = true;
}

void amp::Actor::CallUpdateForComponents()
{
	for (auto& comp : components) {
		comp->update();
	}
}
