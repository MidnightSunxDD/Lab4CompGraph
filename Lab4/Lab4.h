#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "Config.h"
#include "Shader.h"
#include "Cube.h"
#include "Plane.h"

#include <glew/glew.h>

#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

class Lab4
{
private:
	Config* MainConfig;

	GLFWmonitor* MainMonitor;
	const GLFWvidmode* MainVideoMode;

	std::vector < Shader > Shaders;

	std::vector < Cube > Cubes;

	int CUBEAMOUNT = 1;

	void calculateRotation();
public:
	GLFWwindow* MainWindow;
	bool KeyStates[1024];

	int currentColor;
	int currentAxis;
	bool isRotating;
	double currentXRotation;
	double currentYRotation;
	double currentZRotation;
	float rotationSpeed;
	double previousTime;

	Lab4();

	void SetWindowHints();
	int InitializeWindow();
	int InitializeGLFW();
	int InitializeGLEW();

	void Start();
	void Loop();
	void Stop();

	void changeColor();
	void changeAxis();
	void changeRotating();
	
	void increaseRotation();
	void decreaseRotation();
};

