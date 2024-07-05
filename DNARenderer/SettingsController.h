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

class SettingsController {
private:
	bool controlsSettingsActive,
		 windowSettingsActive;
	std::ofstream myfile;
	int windowWidth;
	int windowHeight;
	void windowLoadSettings();
	void windowSaveSettings(int x, int y);

public:
	SettingsController();
	void controlsEvent();
	void windowEvent(GLFWwindow *window);

	bool getControlsSettingsActive();
	bool getWindowSettingsActive();

	void setControlsSettingsActive(bool active);
	void setWindowSettingsActive(bool active);

	int getWindowWidth();
	int getWindowHeight();
	void setWindowHeight(int height);
	void setWindowWidth(int width);
};

#endif