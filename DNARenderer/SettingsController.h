#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class SettingsController {
private:
	bool controlsSettingsActive,
		 windowSettingsActive;
	std::ofstream myfile;
	std::vector<int> windowSettings;

public:
	SettingsController();
	void controlsEvent();
	void windowEvent(GLFWwindow *window);

	bool getControlsSettingsActive();
	bool getWindowSettingsActive();

	void setControlsSettingsActive(bool active);
	void setWindowSettingsActive(bool active);

	void windowSaveSettings(int x, int y);
	void windowLoadSettings();

	std::vector<int> getWindowSettings();
};

#endif