#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <glew/glew.h>

class Shader
{
private:
	std::string VertexShaderFileName;
	std::string FragmentShaderFileName;

	std::string VertexShaderCode;
	std::string FragmentShaderCode;

	GLuint VertexShader;
	GLuint FragmentShader;

	GLuint ShaderProgram;
public:
	Shader();
	Shader(std::string TempVertexShaderFileName, std::string TempFragmentShaderFileName);

	std::string GetVertexShaderFileName();
	void SetVertexShaderFileName(std::string TempVertexShaderFileName);

	std::string GetFragmentShaderFileName();
	void SetFragmentShaderFileName(std::string TempFragmentShaderFileName);

	std::string GetVertexShaderCode();
	void SetVertexShaderCode(std::string TempVertexShaderCode);

	std::string GetFragmentShaderCode();
	void SetFragmentShaderCode(std::string TempFragmentShaderCode);

	GLuint GetVertexShader();
	void SetVertexShader(GLuint TempVertexShader);

	GLuint GetFragmentShader();
	void SetFragmentShader(GLuint TempFragmentShader);

	GLuint GetShaderProgram();
	void SetShaderProgram(GLuint TempShaderProgram);

	void GetVertexShaderCodeFromFile();
	void GetFragmentShaderCodeFromFile();

	int CompileVertexShader();
	int CompileFragmentShader();

	int LinkShadersToProgram();

	void UseShaderProgram();
};

