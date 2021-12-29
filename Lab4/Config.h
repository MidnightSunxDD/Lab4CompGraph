#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum Variables {
	WindowMode,
	WindowWidth,
	WindowHeight,
};

enum VariableValues {
	NoValue,
	WindowModeWindowed,
	WindowModeWindowedBorderless,
	WindowModeFullscreen,
	WindowModeFullscreenBorderless,
};

class Config
{
private:
	std::string ConfigName;
	double* Settings;
public:
	Config();
	Config(std::string TempConfigName);

	std::string GetConfigName();
	void SetConfigName(std::string TempConfigName);

	double *GetSettings();
	void SetSettings(double* TempSettings);

	void GetVariablesFromFile();
	void WriteVariablesToFile();
	
	void GenerateDefaultConfig();

	void SetVariable(int TempVariable, double Value);
	double GetVariable(int TempVariable);
};

