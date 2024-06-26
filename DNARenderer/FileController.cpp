#include "FileController.h"
#

FileController::FileController()
{
    importFailed = false;
}

//------------- UI EVENTS ---------------//

void FileController::menuEvent(DNA& dna) {

    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Delete")) {
            createDialogInstance(".txt");
            deleteSelected = true;
        }
        if (ImGui::MenuItem("Save")) {
            createDialogInstance(".txt");
            saveSelected = true;
        }
        if (ImGui::MenuItem("Import")) {
            createDialogInstance(".txt");
            importSelected = true;
        }
        ImGui::EndMenu();
    }
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) // => will show a dialog
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            std::string filter = ImGuiFileDialog::Instance()->GetCurrentFilter();

            // here convert from string because a string was passed as a userDatas, but it can be what you want
            std::string userDatas;

            if (ImGuiFileDialog::Instance()->GetUserDatas())
                userDatas = std::string((const char*)ImGuiFileDialog::Instance()->GetUserDatas());

            auto selection = ImGuiFileDialog::Instance()->GetSelection(); // multiselection

            // action
            if (deleteSelected) {

            }
            else if (saveSelected) {

            }
            else if (importSelected) {
                dna.setSequence(importSequence(dna, filePathName));
            }
        }
        // close
        ImGuiFileDialog::Instance()->Close();
        saveSelected = false;
        deleteSelected = false;
        importSelected = false;
    }
}

void FileController::createDialogInstance(const char* fileExtension) {
    config.path = ".";
    config.flags = ImGuiFileDialogFlags_Modal;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", fileExtension, config);
}

std::string FileController::importSequence(DNA& dna, std::string& filePath) {
    std::string newSequence = "";
    std::ifstream inputFile(filePath);

    // Check if the file is successfully opened 
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        importFailed = true;
        return "";
    }
    std::string line;
    getline(inputFile, line);
    inputFile.close();

    return line;
}

bool FileController::hasImportFailed() { return importFailed; }