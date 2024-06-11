#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

class SettingsController {
private:
	bool controlsSettingsActive,
		 windowSettingsActive,
		 inputSizeSettingsActive;
public:
	SettingsController();
	void controlsEvent();
	void windowEvent();
	void inputSizeEvent();
	bool getControlsSettingsActive();
	bool getWindowSettingsActive();
	bool getInputSizeSettingsActive();
	void setControlsSettingsActive(bool active);
	void setWindowSettingsActive(bool active);
	void setInputSizeSettingsActive(bool active);
	
};

#endif