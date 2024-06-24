#include "FileController.h"
#

FileController::FileController()
{
}

//------------- UI EVENTS ---------------//

void FileController::menuEvent() {

    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Delete")) {
                IGFD::FileDialogConfig config;
                config.path = ".";
                config.flags = ImGuiFileDialogFlags_Modal;
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", config);
        }
        if (ImGui::MenuItem("Save")) {
            IGFD::FileDialogConfig config;
            config.path = ".";
            config.flags = ImGuiFileDialogFlags_Modal;
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", config);
        }
        if (ImGui::MenuItem("Import")) {
            IGFD::FileDialogConfig config;
            config.path = ".";
            config.flags = ImGuiFileDialogFlags_Modal;
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", config);
        }
        ImGui::EndMenu();
    }
    

    // Display the file dialog and handle actions if OK is pressed
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            std::string filter = ImGuiFileDialog::Instance()->GetCurrentFilter();

            // Convert user data from string if necessary
            std::string userDatas;
            if (ImGuiFileDialog::Instance()->GetUserDatas()) {
                userDatas = std::string((const char*)ImGuiFileDialog::Instance()->GetUserDatas());
            }

            auto selection = ImGuiFileDialog::Instance()->GetSelection(); // Multi-selection

            // Perform your action here with the selected file
        }
        // Close the file dialog
        ImGuiFileDialog::Instance()->Close();
    }
}
