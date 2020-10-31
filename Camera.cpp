#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera(GLFWwindow* win, glm::vec3 pos, glm::vec3 angle, Object* parent, float Fov)
	: Object(pos, angle, parent) {

	FOV = Fov;
	window = win;
	getScene()->cameras.push_back(this);
}

glm::mat4 Camera::getProjectionMatrix() {

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	return glm::perspective(FOV, (float)width / (float)height, 0.01f, 600.f);
}

glm::mat4 Camera::getViewMatrix() {

	glm::mat4 transformMatrix = getTransformMatrix();

	glm::vec3 angle = glm::eulerAngles(glm::quat(glm::quat_cast(transformMatrix)));
	glm::vec4 posFrom = transformMatrix * glm::vec4(0, 0, 0, 1);
	glm::vec3 lookAt = glm::vec3(posFrom.x, posFrom.y, posFrom.z) + glm::vec3(cosf(angle.x) * cosf(angle.y), sinf(angle.y), sinf(angle.x) * cosf(angle.y));

	return glm::lookAt(glm::vec3(posFrom.x, posFrom.y, posFrom.z), lookAt, glm::vec3(0, 1, 0));

}