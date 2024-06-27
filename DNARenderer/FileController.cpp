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
            deleteSelected = true;
            createDialogInstance(".txt");
        }
        if (ImGui::MenuItem("Save")) {
            saveSelected = true;
            createDialogInstance(".txt");
        }
        if (ImGui::MenuItem("Import")) {
            importSelected = true;
            createDialogInstance(".txt");
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

            std::string userDatas;

            if (ImGuiFileDialog::Instance()->GetUserDatas())
                userDatas = std::string((const char*)ImGuiFileDialog::Instance()->GetUserDatas());

            auto selection = ImGuiFileDialog::Instance()->GetSelection(); // multiselection

            // action
            if (deleteSelected) {
                deleteFile(filePathName.c_str());
            }
            else if (saveSelected) {
                saveFile(dna,filePathName.c_str());
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
    if (!saveSelected) {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose a File", fileExtension, config);

    }
    else {
        config.userDatas = IGFDUserDatas("SaveFile");
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Save a File", fileExtension, config);
    }

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

void FileController::deleteFile(const char* filePath) {
    std::remove(filePath);
}

void FileController::saveFile(DNA& dna, const char* filePath) {
    std::ofstream file(filePath);
    std::string sequence = dna.getSequence();
    file.write(sequence.c_str(), sequence.size());
    file.close();
}

bool FileController::hasImportFailed() { return importFailed; }
