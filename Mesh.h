#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"


class Mesh : public Object{
public:

	void Draw();
	std::vector<GLfloat>* getVerticesVector();
	GLuint* getTexture();

	void setup();
	Mesh(glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL);
	~Mesh() override {}

private:

	std::vector<GLfloat> vertices;

	GLuint texture = 0;

	GLuint VAO, VBO, EBO;
	int countTriangles = 0;

	friend void setCube(Mesh*, glm::vec3, glm::vec3, GLuint);
	
};

void setCube(Mesh* mesh, glm::vec3 sides, glm::vec3 color, GLuint texture = GLuint(0));
