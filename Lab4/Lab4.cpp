#include "Lab4.h"

static void window_close_callback(GLFWwindow* window)
{
	Lab4* lab4 = reinterpret_cast<Lab4*>(glfwGetWindowUserPointer(window));
	glfwSetWindowShouldClose((*lab4).MainWindow, GL_TRUE);
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Lab4* lab4 = reinterpret_cast<Lab4*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) (*lab4).changeAxis();
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) (*lab4).increaseRotation();
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) (*lab4).decreaseRotation();
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) (*lab4).KeyStates[key] = true;
		else (*lab4).KeyStates[key] = false;
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Lab4* lab4 = reinterpret_cast<Lab4*>(glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) (*lab4).changeColor();
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) (*lab4).changeRotating();
}

static glm::vec3 getColor(int i) {
	switch (i)
	{
	case 0:
		return glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case 1:
		return glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case 2:
		return glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	default:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	}
}

Lab4::Lab4()
{
	MainConfig = new Config();
	MainMonitor = nullptr;
	MainVideoMode = nullptr;
	MainWindow = nullptr;

	for (int i = 0; i < 1024; i++) KeyStates[i] = false;

	currentColor = 0;
	isRotating = true;
	currentXRotation = 0.0;
	currentYRotation = 0.0;
	currentZRotation = 0.0;
	rotationSpeed = 60.0f;
	currentAxis = 0;
	previousTime = 0.0;
}

void Lab4::SetWindowHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (MainConfig->GetVariable(Variables::WindowMode) == VariableValues::WindowModeWindowed) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	}
	else if (MainConfig->GetVariable(Variables::WindowMode) == VariableValues::WindowModeWindowedBorderless) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	}
	else if (MainConfig->GetVariable(Variables::WindowMode) == VariableValues::WindowModeFullscreen) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
	else if (MainConfig->GetVariable(Variables::WindowMode) == VariableValues::WindowModeFullscreenBorderless) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RED_BITS, MainVideoMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, MainVideoMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, MainVideoMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, MainVideoMode->refreshRate);
	}
	else {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	}
}

int Lab4::InitializeWindow()
{
	MainMonitor = glfwGetPrimaryMonitor();
	MainVideoMode = glfwGetVideoMode(MainMonitor);
	SetWindowHints();
	if (MainConfig->GetVariable(Variables::WindowMode) == VariableValues::WindowModeWindowed || MainConfig->GetVariable(Variables::WindowMode) == VariableValues::WindowModeWindowedBorderless) {
		MainWindow = glfwCreateWindow((int)MainConfig->GetVariable(Variables::WindowWidth), (int)MainConfig->GetVariable(Variables::WindowHeight), "Lab4", NULL, NULL);
		glViewport(0, 0, (GLint)MainConfig->GetVariable(Variables::WindowWidth), (GLint)MainConfig->GetVariable(Variables::WindowHeight));
	}
	else {
		MainWindow = glfwCreateWindow((int)MainConfig->GetVariable(Variables::WindowWidth), (int)MainConfig->GetVariable(Variables::WindowHeight), "Lab4", MainMonitor, NULL);
		glViewport(0, 0, MainVideoMode->width, MainVideoMode->height);
	}

	glfwSetWindowSizeLimits(MainWindow, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);

	const char* ErrorInfo;
	if (MainWindow == nullptr) {
		int Code = glfwGetError(&ErrorInfo);
		std::cout << "Failed to create window. Error code: " << std::hex << std::showbase << Code << std::endl;
		std::cout << "Error description: " << ErrorInfo << std::endl;
		char Temp = getchar();
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(MainWindow);

	glfwSetWindowUserPointer(MainWindow, reinterpret_cast<void*>(this));
	return 0;
}

int Lab4::InitializeGLFW()
{
	int Success = glfwInit();
	const char* ErrorInfo;
	if (Success == GLFW_FALSE) {
		int Code = glfwGetError(&ErrorInfo);
		std::cout << "Failed to initialize GLFW. Error code: " << std::hex << Code << std::endl;
		std::cout << "Error description: " << ErrorInfo << std::endl;
		char Temp = getchar();
		glfwTerminate();
		return 1;
	}
	return 0;
}

int Lab4::InitializeGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW\n";
		char Temp = getchar();
		glfwTerminate();
		return 1;
	}
	return 0;
}

void Lab4::Start()
{
	srand((unsigned int)time(0));
	if (InitializeGLFW()) return;
	if (InitializeWindow()) return;
	if (InitializeGLEW()) return;
	Shaders.push_back(Shader("VertexShader.glsl", "FragmentShader.glsl"));
	if (Shaders.back().CompileVertexShader()) {
		glfwTerminate();
		return;
	}
	if (Shaders.back().CompileFragmentShader()) {
		glfwTerminate();
		return;
	}
	if (Shaders.back().LinkShadersToProgram()) {
		glfwTerminate();
		return;
	}

	GLenum b = glGetError();

	Cubes.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	Cubes.back().InitializeObject();
	/*for (int i = 0; i < CUBEAMOUNT; i++) {
		Cubes.push_back(Cube(glm::vec3((rand() % 2000 - 1000) / 100.0f, (rand() % 2000 - 1000) / 100.0f, -5.0f)));
		Cubes.back().InitializeObject();
	}*/

	glEnable(GL_DEPTH_TEST);

	glfwSetWindowCloseCallback(MainWindow, window_close_callback);
	glfwSetWindowSizeCallback(MainWindow, window_size_callback);
	glfwSetFramebufferSizeCallback(MainWindow, framebuffer_size_callback);
	glfwSetKeyCallback(MainWindow, key_callback);
	glfwSetMouseButtonCallback(MainWindow, mouse_button_callback);

	Loop();
}

void Lab4::Loop()
{
	while (!glfwWindowShouldClose(MainWindow)) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < CUBEAMOUNT; i++) {
			Shaders.back().UseShaderProgram();

			GLint ModelLocation = glGetUniformLocation(Shaders.back().GetShaderProgram(), "Model");
			GLint ViewLocation = glGetUniformLocation(Shaders.back().GetShaderProgram(), "View");
			GLint ProjectionLocation = glGetUniformLocation(Shaders.back().GetShaderProgram(), "Projection");
			GLint VertexColorLocation = glGetUniformLocation(Shaders.back().GetShaderProgram(), "VertexColor");

			glBindVertexArray(Cubes[i].GetVAO());

			glm::mat4 Model = glm::mat4(1.0f);
			glm::mat4 View = glm::mat4(1.0f);
			glm::mat4 Projection = glm::mat4(1.0f);
			glm::vec3 Color = getColor(currentColor);

			Model = glm::translate(Model, Cubes[i].GetPosition());
			Model = glm::rotate(Model, (float)currentXRotation, glm::vec3(1.0f, 0.0f, 0.0f));
			Model = glm::rotate(Model, (float)currentYRotation, glm::vec3(0.0f, 1.0f, 0.0f));
			Model = glm::rotate(Model, (float)currentZRotation, glm::vec3(0.0f, 0.0f, 1.0f));
			View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f));
			Projection = glm::perspective(90.0f, (GLfloat)(MainConfig->GetVariable(Variables::WindowWidth)) / (GLfloat)(MainConfig->GetVariable(Variables::WindowHeight)), 0.1f, 100.0f);
		
			glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));
			glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(View));
			glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, glm::value_ptr(Projection));
			glUniform3fv(VertexColorLocation, 1, glm::value_ptr(Color));

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glDrawElements(GL_TRIANGLES, 3 * Cubes[i].GetTriangleAmount(), GL_UNSIGNED_INT, 0);

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(3.0f);
			glm::vec3 BlackColor = getColor(3);
			glUniform3fv(VertexColorLocation, 1, glm::value_ptr(BlackColor));

			glDrawElements(GL_TRIANGLES, 3 * Cubes[i].GetTriangleAmount(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}

		if (isRotating) calculateRotation();

		glfwSwapBuffers(MainWindow);

		glfwPollEvents();
	}

	Stop();
}

void Lab4::Stop()
{
	glfwDestroyWindow(MainWindow);
	glfwTerminate();
}

void Lab4::changeColor()
{
	currentColor = (currentColor + 1) % 3;
}

void Lab4::changeAxis()
{
	currentAxis = (currentAxis + 1) % 3;
}

void Lab4::changeRotating()
{
	if (isRotating) {
		isRotating = false;
	}
	else {
		isRotating = true;
		previousTime = glfwGetTime();
	}
}

void Lab4::increaseRotation()
{
	rotationSpeed = rotationSpeed + 5.0f;
	if (rotationSpeed > 360.0f) rotationSpeed = 360.0f;
}

void Lab4::decreaseRotation()
{
	rotationSpeed = rotationSpeed - 5.0f;
	if (rotationSpeed < -360.0f) rotationSpeed = -360.0f;
}

void Lab4::calculateRotation()
{
	double time = glfwGetTime();
	if (currentAxis == 0) currentXRotation += (time - previousTime) * glm::radians(rotationSpeed);
	else if (currentAxis == 1) currentYRotation += (time - previousTime) * glm::radians(rotationSpeed);
	else currentZRotation += (time - previousTime) * glm::radians(rotationSpeed);
	previousTime = time;
}