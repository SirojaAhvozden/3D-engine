#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
#include <iostream>

//std::vector<GLuint> texs;

void Mesh::Draw() {

	if (!scene->shaderCollector.isShaderExists(MySkeletonShader)) return;

	GLuint shader = scene->shaderCollector.getShader(MySkeletonShader);

	glUseProgram(shader);

	GLuint viewLoc = glGetUniformLocation(shader, "view");
	GLuint projectionLoc = glGetUniformLocation(shader, "projection");

	glm::mat4 view = scene->getViewMatrix();
	glm::mat4 projection = scene->getProjectionMatrix();

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 transform = getTransformMatrix();
	GLuint transformLoc = glGetUniformLocation(shader, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE , &transform[0][0]);

	glm::vec3 ambient = scene->getAmbientLightColor() * scene->getAmbientLightStrength();
	GLuint ambientLoc = glGetUniformLocation(shader, "ambient");
	glUniform3f(ambientLoc, ambient.x, ambient.y, ambient.z);

	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 11);
	glBindVertexArray(0);

}

std::vector<GLfloat>* Mesh::getVerticesVector() {
	return &vertices;
}

GLuint* Mesh::getTexture() {
	return &texture;
}

void Mesh::setup(/*GLuint tex*/) {

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (GLvoid*)(8 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	
	//std::cout << &textures << " textures\n";
		
}

void setCube(Mesh* mesh, glm::vec3 sides, glm::vec3 color, GLuint texture){

	glm::vec3 side(fabsf(sides.x), fabsf(sides.y), fabsf(sides.z));

	float texY = side.y / (side.y + 2 * side.z);
	float texX = side.x / (2 * (side.x + side.z));
	float texZ_w = side.z / (2 * (side.x + side.z));
	float texZ_h = side.z / (2 * side.z + side.y);

	std::vector <GLfloat> vertices = {

		0, 0, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, texY,						0,0,-1,	//
		1, 0, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, texY,					0,0,-1,	//			это
		0, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, 0,						0,0,-1,	//			левая( -z )
																																	//
		1, 0, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, texY,					0,0,-1,	//			грань
		0, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, 0,						0,0,-1,	//			куба
		1, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, 0,						0,0,-1,	//

		1, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX + texZ_w, 0,			1,0,0,	//
		1, 1, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, 0,						1,0,0,	//			это 
		1, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, texY,					1,0,0,	//			передняя( +x )
																																	//
		1, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX + texZ_w, 0,			1,0,0,	//			грань
		1, 0, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX + texZ_w, texY,			1,0,0,	//			куба
		1, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, texY,					1,0,0,	//

		0, 1, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX + texZ_w, 0,			0,0,1,	//
		1, 1, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 2 * texX + texZ_w, 0,		0,0,1,	//			это
		1, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 2 * texX + texZ_w, texY,		0,0,1,	//			правая( +z )
																																	//
		0, 1, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX + texZ_w, 0,			0,0,1,	//			грань
		0, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX + texZ_w, texY,			0,0,1,	//			куба
		1, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 2 * texX + texZ_w, texY,		0,0,1,	//

		0, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 1 - texZ_w, 0,				-1,0,0,	//
		0, 1, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 1, 0,						-1,0,0,	//			это
		0, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 1, texY,						-1,0,0,	//			задняя ( -x )
																																	//
		0, 0, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 1 - texZ_w, texY,			-1,0,0,	//			грань
		0, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 1 - texZ_w, 0,				-1,0,0,	//			куба
		0, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 1, texY,						-1,0,0,	//

		0, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, texY,						0,1,0,	//
		1, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, texY,					0,1,0,	//			это
		1, 1, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, texY + texZ_h,			0,1,0,	//			верхняя ( +y )
																																	//	
		0, 1, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, texY,						0,1,0,	//			грань
		0, 1, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, texY + texZ_h,			0,1,0,	//			куба (наложение текстуры от -z до +z)
		1, 1, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, texY + texZ_h,			0,1,0,	//

		0, 0, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, texY + texZ_h,			0,-1,0,	//
		1, 0, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, texY + texZ_h,			0,-1,0,	//			это 
		1, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, 1,						0,-1,0,	//			нижняя ( -y )
																																	//
		0, 0, 0,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, texY + texZ_h,			0,-1,0,	//			грань
		0, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, 0, 1,						0,-1,0,	//			куба (наложение текстуры от -z до +z)
		1, 0, 1,							color.x / 255.f, color.y / 255.f, color.z / 255.f, texX, 1,						0,-1,0,	//

	};

	for (int i = 0; i < vertices.size() / 11; i++) {
		vertices[i * 11] = vertices[i * 11] * sides.x;
		vertices[i * 11 + 1] = vertices[i * 11 + 1] * sides.y;
		vertices[i * 11 + 2] = vertices[i * 11 + 2] * sides.z;
	}
	
	/*for (int i = 0; i < vertices.size() / 8; i++) {
		vertices[i * 8 + 6] *= fabsf(sides.x) / sides.x;
		vertices[i * 8 + 7] *= fabsf(sides.y) / sides.y;
	}*/

	if (texture == 0) {
		for (int i = 0; i < vertices.size() / 11; i++) {
			vertices[i * 11 + 6] = -2;
			vertices[i * 11 + 7] = -2;
		}
	}

	

	mesh->texture = texture;
	mesh->vertices = vertices;

	//std::cout << mesh.getVerticesVector()->size() << std::endl;

	/*for (int i = 0; i < mesh.getVerticesVector()->size(); i++) {
		std::cout << mesh.getVerticesVector()->at(i) << " ";
		if ((i + 1) % 6 == 0) std::cout << std::endl;
	}*/

	//mesh.getIndicesVector()->insert(mesh.getIndicesVector()->end(), addindices.begin(), addindices.end());
	//std::cout << mesh.getIndicesVector()->size();
	mesh->setup();
}

Mesh::Mesh(glm::vec3 pos, glm::vec3 angle, Object* parent)
	: Object(pos, angle, parent)
{
	getScene()->meshes.push_back(this);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}
