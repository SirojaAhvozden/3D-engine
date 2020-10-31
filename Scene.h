#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "ShaderCollector.h"

class Object;
class Mesh;
class Actor;
class Camera;

class Scene {
public:

	void draw();
	void update(float sec);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	std::vector<Object*> objects;
	std::vector<Mesh*> meshes;
	std::vector<Actor*> actors;
	std::vector<Camera*> cameras;

	ShaderCollector shaderCollector;
	glm::vec3 getAmbientLightColor();
	float getAmbientLightStrength();

	Camera* activeCam;
};