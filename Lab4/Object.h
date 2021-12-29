#pragma once

#include <iostream>
#include <string>

#include <glew/glew.h>

#include <GLM/glm.hpp>

class Object
{
private:

public:
	Object();
	Object(glm::vec3 TempPosition);

	virtual ~Object();

	GLfloat* GetVertexData();
	void SetVertexData(GLfloat* TempVertexData);

	GLuint GetVertexAmount();
	void SetVertexAmount(GLuint TempVertexAmount);

	GLuint* GetIndexData();
	void SetIndexData(GLuint* TempIndexData);

	GLuint GetTriangleAmount();
	void SetTriangleAmount(GLuint TempTriangleAmount);

	GLuint GetVAO();
	void SetVAO(GLuint TempVAO);

	GLuint GetVertexVBO();
	void SetVertexVBO(GLuint TempVertexVBO);

	GLuint GetEBO();
	void SetEBO(GLuint TempEBO);

	glm::vec3 GetPosition();
	void SetPositon(glm::vec3 TempPosition);

	void InitializeObject();

protected:
	GLfloat* VertexData;
	GLuint VertexAmount;

	GLuint* IndexData;
	GLuint TriangleAmount;

	GLuint VAO;
	GLuint VertexVBO;
	GLuint EBO;

	glm::vec3 Position;

	void Constructor();
};
