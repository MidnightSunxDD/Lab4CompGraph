#pragma once

#include "Object.h"

class Plane : public Object
{
private:

public:
	Plane();
	Plane(glm::vec3 TempPosition);

protected:
	void Constructor();

};