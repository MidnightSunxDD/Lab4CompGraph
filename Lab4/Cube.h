#pragma once

#include "Object.h"

class Cube : public Object
{
private:

public:
	Cube();
	Cube(glm::vec3 TempPosition);

protected:
	void Constructor();

};
