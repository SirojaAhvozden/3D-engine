#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "LoadGLSL.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <math.h>

#include "Mesh.h"
#include "Bone.h"
#include "Skeleton.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "Scene.h"
#include "InputObject.h"
#include "Input.h"

Scene scene;

#pragma comment (lib,"DevIL.lib")
#pragma comment (lib,"ilut.lib")
#pragma comment (lib,"ilu.lib")

#define GLEW_STATIC

using namespace glm;

float z = -3;
float x = 0;
float y = 1.62;

GLFWwindow* window;

int main() {

	ilInit();
	iluInit();

	if (glfwInit() == -1) {
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "FPS", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error to opening window";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true; // Флаг необходим в Core-режиме OpenGL. Инициализируем GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return -1;
	}

	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, keyCallBack);
	glfwSetCursorPosCallback(window, mouseCallBack);

	glEnable(GL_DEPTH_TEST);

	Scene scene;
	Object::setScene(&scene);
	Skeleton skeleton;
	InputObject camBasic(glm::vec3(0, 4, 0), glm::vec3(glm::radians(0.f), glm::radians(0.f), glm::radians(0.f))/*, skeleton.getBones()->back()*/);
	Camera camera(window, glm::vec3(0), glm::vec3(0), &camBasic);

	GLuint shaderProgram = LoadShaders("Vertex shader.glsl", "Fragment shader.glsl");
	GLuint shaderCube = LoadShaders("Vertex Shader2.glsl", "Fragment shader2.glsl");

	scene.shaderCollector.addShader(MySkeletonShader, shaderCube);
	scene.shaderCollector.addShader(SimplestShader, shaderProgram);

	float time = glfwGetTime();

	while (glfwWindowShouldClose(window) == 0) {
		
		float currentTime = glfwGetTime();

		float seconds = currentTime - time;
		seconds *= 2;

		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.update(seconds);
		Input::resetMouseOffset();
		scene.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		time = currentTime;
	}

	glfwTerminate();

	return 0;
}