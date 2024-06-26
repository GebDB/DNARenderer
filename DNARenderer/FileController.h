#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>
#include <ImGuiFileDialog/ImGuiFileDialog.h>
#include <ImGUIFileDialog/ImGuiFileDialogConfig.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <DNA.h>


class FileController {
private:
	IGFD::FileDialogConfig config;
	bool deleteSelected;
	bool saveSelected;
	bool importSelected;
	bool importFailed;
public:
	FileController();
	void menuEvent(DNA& dna);
	void createDialogInstance(const char* fileExtension);
	std::string importSequence(DNA& dna, std::string& filePath);
	bool hasImportFailed();
};

#endif