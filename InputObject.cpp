#include "InputObject.h"
#include "Input.h"

void InputObject::update(float sec) {

	glm::vec3 angle = glm::eulerAngles(glm::quat(glm::quat_cast(transformMatrix)));
	glm::vec4 pos = transformMatrix * glm::vec4(0, 0, 0, 1);

	if (Input::keyPressed[GLFW_KEY_W]) {
		pos.x += cosf(angle.x) * cosf(angle.y) * sec;
		pos.y += sinf(angle.y) * sec;
		pos.z += sinf(angle.x) * cosf(angle.y) * sec;
	}
	if (Input::keyPressed[GLFW_KEY_S]) {
		pos.x -= cosf(angle.x) * cosf(angle.y) * sec;
		pos.y -= sinf(angle.y) * sec;
		pos.z -= sinf(angle.x) * cosf(angle.y) * sec;
	}
	if (Input::keyPressed[GLFW_KEY_D]) {
		pos.x += cosf(angle.x + glm::radians(90.f)) * sec;
		pos.z += sinf(angle.x + glm::radians(90.f)) * sec;
	}
	if (Input::keyPressed[GLFW_KEY_A]) {
		pos.x -= cosf(angle.x + glm::radians(90.f)) * sec;
		pos.z -= sinf(angle.x + glm::radians(90.f)) * sec;
	}

	glm::mat4 mat(1.f);
	mat = translate(mat, glm::vec3(pos.x, pos.y, pos.z));

	angle.x += glm::radians(Input::mouseOffsetX * 3.14 * 4 / WIDTH);
	if (angle.x > 3.14) {
		angle.x -= 2 * 3.14;
	}
	if (angle.x < -3.14) {
		angle.x += 2 * -3.14;
	}
	angle.y -= glm::radians(Input::mouseOffsetY * 3.14 * 4 / HEIGHT);
	if (angle.y > 3.14) {
		angle.y = 3.14;
	}
	if (angle.y < -3.14) {
		angle.y = -3.14;
	}

	transformMatrix = mat * glm::mat4_cast(glm::quat(angle));
}