#include "Shader.h"

Shader::Shader()
{
	VertexShaderFileName = "";
	FragmentShaderFileName = "";
	VertexShaderCode = "";
	FragmentShaderCode = "";
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ShaderProgram = glCreateProgram();
}

Shader::Shader(std::string TempVertexShaderName, std::string TempFragmentShaderName)
{
	VertexShaderFileName = TempVertexShaderName;
	FragmentShaderFileName = TempFragmentShaderName;
	VertexShaderCode = "";
	FragmentShaderCode = "";
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ShaderProgram = glCreateProgram();
}

std::string Shader::GetVertexShaderFileName()
{
	return VertexShaderFileName;
}

void Shader::SetVertexShaderFileName(std::string TempVertexShaderFileName)
{
	VertexShaderFileName = TempVertexShaderFileName;
}

std::string Shader::GetFragmentShaderFileName()
{
	return FragmentShaderFileName;
}

void Shader::SetFragmentShaderFileName(std::string TempFragmentShaderFileName)
{
	FragmentShaderFileName = TempFragmentShaderFileName;
}

std::string Shader::GetVertexShaderCode()
{
	return VertexShaderCode;
}

void Shader::SetVertexShaderCode(std::string TempVertexShaderCode)
{
	VertexShaderCode = TempVertexShaderCode;
}

std::string Shader::GetFragmentShaderCode()
{
	return FragmentShaderCode;
}

void Shader::SetFragmentShaderCode(std::string TempFragmentShaderCode)
{
	FragmentShaderCode = TempFragmentShaderCode;
}

GLuint Shader::GetVertexShader()
{
	return VertexShader;
}

void Shader::SetVertexShader(GLuint TempVertexShader)
{
	VertexShader = TempVertexShader;
}

GLuint Shader::GetFragmentShader()
{
	return FragmentShader;
}

void Shader::SetFragmentShader(GLuint TempFragmentShader)
{
	FragmentShader = TempFragmentShader;
}

GLuint Shader::GetShaderProgram()
{
	return ShaderProgram;
}

void Shader::SetShaderProgram(GLuint TempShaderProgram)
{
	ShaderProgram = TempShaderProgram;
}

void Shader::GetVertexShaderCodeFromFile()
{
	if (!VertexShaderFileName.empty()) {
		std::ifstream Input(VertexShaderFileName);
		if (!Input.good()) {
			std::cout << "Failed to open vertex shader code file\n";
			return;
		}
		std::string Temp;
		while (getline(Input, Temp)) VertexShaderCode += Temp + "\n";
		Input.close();
	}
}

void Shader::GetFragmentShaderCodeFromFile()
{
	if (!FragmentShaderFileName.empty()) {
		std::ifstream Input(FragmentShaderFileName);
		if (!Input.good()) {
			std::cout << "Failed to open fragment shader code file\n";
			return;
		}
		std::string Temp;
		while (getline(Input, Temp)) FragmentShaderCode += Temp + "\n";
		Input.close();
	}
}

int Shader::CompileVertexShader()
{
	if (VertexShaderCode.empty()) GetVertexShaderCodeFromFile();
	if (VertexShaderCode.empty()) {
		std::cout << "Failed to get vertex shader code from file\n";
		char Temp = getchar();
		return 1;
	}

	const char* VertexShaderCodeCString = VertexShaderCode.c_str();
	glShaderSource(VertexShader, 1, &VertexShaderCodeCString, NULL);
	glCompileShader(VertexShader);

	GLchar ShaderCompilationInfo[512];
	int Success;
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
	if (Success == 0) {
		glGetShaderInfoLog(VertexShader, 512, NULL, ShaderCompilationInfo);
		std::cout << "Failed to compile vertex shader\n";
		std::cout << "Error description: " << ShaderCompilationInfo << std::endl;
		char Temp = getchar();
		return 1;
	}

	return 0;
}

int Shader::CompileFragmentShader()
{
	if (FragmentShaderCode.empty()) GetFragmentShaderCodeFromFile();
	if (VertexShaderCode.empty()) {
		std::cout << "Failed to get fragment shader code from file\n";
		char Temp = getchar();
		return 1;
	}

	const char* FragmentShaderCodeCString = FragmentShaderCode.c_str();
	glShaderSource(FragmentShader, 1, &FragmentShaderCodeCString, NULL);
	glCompileShader(FragmentShader);

	GLchar ShaderCompilationInfo[512];
	int Success;
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
	if (Success == 0) {
		glGetShaderInfoLog(FragmentShader, 512, NULL, ShaderCompilationInfo);
		std::cout << "Failed to compile Fragment shader\n";
		std::cout << "Error description: " << ShaderCompilationInfo << std::endl;
		char Temp = getchar();
		return 1;
	}

	return 0;
}

int Shader::LinkShadersToProgram()
{
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	GLchar ProgramLinkInfo[512];
	int Success;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, 512, NULL, ProgramLinkInfo);
		std::cout << "Failed to link shaders to shader program\n";
		std::cout << "Error description: " << ProgramLinkInfo << std::endl;
		char Temp = getchar();
		return 1;
	}
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	return 0;
}

void Shader::UseShaderProgram()
{
	glUseProgram(ShaderProgram);
}