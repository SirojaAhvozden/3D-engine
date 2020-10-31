#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Object.h"
#include "Actor.h"

glm::mat4 Scene::getProjectionMatrix() {
	return activeCam->getProjectionMatrix();
}

glm::mat4 Scene::getViewMatrix() {
	return activeCam->getViewMatrix();
}

glm::vec3 Scene::getAmbientLightColor() {
	return glm::vec3(1, 1, 1);
}

float Scene::getAmbientLightStrength() {
	return 0.7f;
}

void Scene::draw() {

	if (activeCam == NULL) {
		if (cameras.size() > 0)
			activeCam = cameras[0];
	}

	for (auto a : meshes) {

		a->Draw();

	}

}

void Scene::update(float sec) {

	for (auto a : actors) {
		a->update(sec);
	}

}