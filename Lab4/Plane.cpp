#include "Plane.h"


Plane::Plane() : Object()
{
	Constructor();
}

Plane::Plane(glm::vec3 TempPosition) : Object(TempPosition)
{
	Constructor();
}

void Plane::Constructor()
{
	VertexData = new GLfloat[12]{
		// FRONT
		-1.0, -1.0, 0.0,
		-1.0, 1.0, 0.0,
		1.0, 1.0, 0.0,
		1.0, -1.0, 0.0
	};
	VertexAmount = 4;

	IndexData = new GLuint[36]{
		0, 3, 2,
		0, 2, 1
	};
	TriangleAmount = 2;
}