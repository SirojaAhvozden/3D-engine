#pragma once
#include "Actor.h"

class InputObject : public Actor {
public:

	void update(float sec) override;
	InputObject(glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL)
		: Actor(pos, angle, parent) {
	
	}

};
