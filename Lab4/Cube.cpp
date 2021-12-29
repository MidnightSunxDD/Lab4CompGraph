#include "Cube.h"

Cube::Cube() : Object()
{
	Constructor();
}

Cube::Cube(glm::vec3 TempPosition) : Object(TempPosition)
{
	Constructor();
}

void Cube::Constructor()
{
	VertexData = new GLfloat[72]{
		// FRONT
		-2.0, -1.0, 1.0,
		-2.0, 1.0, 1.0,
		2.0, 1.0, 1.0,
		2.0, -1.0, 1.0,
		// RIGHT
		2.0, -1.0, 1.0,
		2.0, 1.0, 1.0,
		2.0, 1.0, -1.0,
		2.0, -1.0, -1.0,
		// BACK
		2.0, -1.0, -1.0,
		2.0, 1.0, -1.0,
		-2.0, 1.0, -1.0,
		-2.0, -1.0, -1.0,
		// LEFT
		-2.0, -1.0, -1.0,
		-2.0, 1.0, -1.0,
		-2.0, 1.0, 1.0,
		-2.0, -1.0, 1.0,
		// TOP
		-2.0, 1.0, 1.0,
		-2.0, 1.0, -1.0,
		2.0, 1.0, -1.0,
		2.0, 1.0, 1.0,
		// BOTTOM
		-2.0, -1.0, 1.0,
		-2.0, -1.0, -1.0,
		2.0, -1.0, -1.0,
		2.0, -1.0, 1.0,
	};
	VertexAmount = 24;

	IndexData = new GLuint[36]{
		// FRONT
		0, 3, 2,
		0, 2, 1,
		// RIGHT
		4, 7, 6,
		4, 6, 5,
		// BACK
		8, 11, 10,
		8, 10, 9,
		// LEFT
		12, 15, 14,
		12, 14, 13,
		// TOP
		16, 19, 18,
		16, 18, 17,
		// BOTTOM
		20, 21, 22,
		20, 22, 23
	};
	TriangleAmount = 12;
}