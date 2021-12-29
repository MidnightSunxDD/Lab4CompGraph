#include "Config.h"

Config::Config()
{
	ConfigName = "Config.ini";
	Settings = new double[256];
	std::ifstream Input(ConfigName);
	if (!Input.good()) {
		std::cout << "Failed to open config file\n";
		GenerateDefaultConfig();
		return;
	}
	GetVariablesFromFile();
}

Config::Config(std::string TempConfigName)
{
	ConfigName = TempConfigName;
	Settings = new double[256];
	std::ifstream Input(ConfigName);
	if (!Input.good()) {
		std::cout << "Failed to open config file\n";
		ConfigName = "Config.ini";
		GenerateDefaultConfig();
		return;
	}
	GetVariablesFromFile();
}

std::string Config::GetConfigName()
{
	return ConfigName;
}

void Config::SetConfigName(std::string TempConfigName)
{
	ConfigName = TempConfigName;
}

double *Config::GetSettings()
{
	return Settings;
}

void Config::SetSettings(double* TempSettings)
{
	Settings = TempSettings;
}

void Config::GetVariablesFromFile()
{
	if (ConfigName.empty()) {
		std::cout << "No config name\n";
		ConfigName = "Config.ini";
	}
	std::ifstream Input(ConfigName);
	if (!Input.good()) {
		std::cout << "Failed to open config file\n";
		ConfigName = "Config.ini";
		GenerateDefaultConfig();
		return;
	}
	while (!Input.eof()) {
		std::string Variable;
		char Temp;
		bool Flag = true;
		while (Flag && !Input.eof()) {
			Input.get(Temp);
			if (Temp == ':' || Input.eof()) Flag = false;
			else Variable += Temp;
		}

		std::string Value;
		Flag = true;
		while (Flag && !Input.eof()) {
			Input.get(Temp);
			if (Temp == ';' || Input.eof()) Flag = false;
			else Value += Temp;
		}
		Input.get(Temp);

		if (Variable == "WindowMode") {
			if (Value == "WindowModeWindowed") Settings[Variables::WindowMode] = VariableValues::WindowModeWindowed;
			else if (Value == "WindowModeWindowedBorderless") Settings[Variables::WindowMode] = VariableValues::WindowModeWindowedBorderless;
			else if (Value == "WindowModeFullscreen") Settings[Variables::WindowMode] = VariableValues::WindowModeFullscreen;
			else if (Value == "WindowModeFullscreenBorderless") Settings[Variables::WindowMode] = VariableValues::WindowModeFullscreenBorderless;
		}
		else if (Variable == "WindowWidth") {
			Settings[Variables::WindowWidth] = std::stod(Value);
		}
		else if (Variable == "WindowHeight") {
			Settings[Variables::WindowHeight] = std::stod(Value);
		}
	}
	Input.close();
}

void Config::WriteVariablesToFile()
{
	if (ConfigName.empty()) {
		std::cout << "No config name\n";
		ConfigName = "Config.ini";
	}
	std::ofstream Output(ConfigName);
	if (!Output.good()) {
		std::cout << "Failed to write config file\n";
		return;
	}

	if (Settings[Variables::WindowMode] == VariableValues::WindowModeWindowed) Output << "WindowMode:WindowModeWindowed;\n";
	else if (Settings[Variables::WindowMode] == VariableValues::WindowModeWindowedBorderless) Output << "WindowMode:WindowModeWindowedBorderless;\n";
	else if (Settings[Variables::WindowMode] == VariableValues::WindowModeFullscreen) Output << "WindowMode:WindowModeFullscreen;\n";
	else if (Settings[Variables::WindowMode] == VariableValues::WindowModeFullscreenBorderless) Output << "WindowMode:WindowModeFullscreenBorderless;\n";
	else Output << "WindowMode:;\n";

	Output << "WindowWidth:" << (int)Settings[Variables::WindowWidth] << ";\n";
	Output << "WindowHeight:" << (int)Settings[Variables::WindowHeight] << ";\n";

	Output.close();
}

void Config::GenerateDefaultConfig()
{
	Settings[Variables::WindowMode] = VariableValues::WindowModeWindowed;
	Settings[Variables::WindowWidth] = 800;
	Settings[Variables::WindowHeight] = 600;
	WriteVariablesToFile();
}

void Config::SetVariable(int TempVariable, double Value)
{
	if (TempVariable == Variables::WindowMode) Settings[Variables::WindowMode] = Value;
	else if (TempVariable == Variables::WindowWidth) Settings[Variables::WindowWidth] = Value;
	else if (TempVariable == Variables::WindowHeight) Settings[Variables::WindowHeight] = Value;
}

double Config::GetVariable(int TempVariable)
{
	if (TempVariable == Variables::WindowMode) return Settings[Variables::WindowMode];
	else if (TempVariable == Variables::WindowWidth) return Settings[Variables::WindowWidth];
	else if (TempVariable == Variables::WindowHeight) return Settings[Variables::WindowHeight];
	return NoValue;
}