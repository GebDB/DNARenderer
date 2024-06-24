#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>
#include <ImGuiFileDialog/ImGuiFileDialog.h>
#include <ImGUIFileDialog/ImGuiFileDialogConfig.h>


class FileController {
private:

public:
	FileController();
	void menuEvent();
};

#endif