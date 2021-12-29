#include "Object.h"

Object::Object()
{
	Constructor();

	Position = glm::vec3(0.0, 0.0, 0.0);
}

Object::Object(glm::vec3 TempPosition)
{
	Constructor();

	Position = TempPosition;
}

Object::~Object()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VertexVBO);
	glDeleteBuffers(1, &EBO);
}

void Object::Constructor()
{
	VertexData = nullptr;
	VertexAmount = 0;

	IndexData = nullptr;
	TriangleAmount = 0;
}

GLfloat* Object::GetVertexData()
{
	return VertexData;
}

void Object::SetVertexData(GLfloat* TempVertexData)
{
	VertexData = TempVertexData;
}

GLuint Object::GetVertexAmount()
{
	return VertexAmount;
}

void Object::SetVertexAmount(GLuint TempVertexAmount)
{
	VertexAmount = TempVertexAmount;
}

GLuint* Object::GetIndexData()
{
	return IndexData;
}

void Object::SetIndexData(GLuint* TempIndexData)
{
	IndexData = TempIndexData;
}

GLuint Object::GetTriangleAmount()
{
	return TriangleAmount;
}

void Object::SetTriangleAmount(GLuint TempTriangleAmount)
{
	TriangleAmount = TempTriangleAmount;
}

GLuint Object::GetVAO()
{
	return VAO;
}

void Object::SetVAO(GLuint TempVAO)
{
	VAO = TempVAO;
}

GLuint Object::GetVertexVBO()
{
	return VertexVBO;
}

void Object::SetVertexVBO(GLuint TempVertexVBO)
{
	VertexVBO = TempVertexVBO;
}

GLuint Object::GetEBO()
{
	return EBO;
}

void Object::SetEBO(GLuint TempEBO)
{
	EBO = TempEBO;
}

glm::vec3 Object::GetPosition()
{
	return Position;
}

void Object::SetPositon(glm::vec3 TempPosition)
{
	Position = TempPosition;
}

void Object::InitializeObject()
{
	if (VertexAmount == 0 || TriangleAmount == 0 || VertexData == nullptr || IndexData == nullptr) {
		std::cout << "Failed to initialize object\n";
		return;
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, VertexVBO);
	glBufferData(GL_ARRAY_BUFFER, (long long)3 * VertexAmount * sizeof(GLfloat), VertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long long)3 * TriangleAmount * sizeof(GLuint), IndexData, GL_STATIC_DRAW);


	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}