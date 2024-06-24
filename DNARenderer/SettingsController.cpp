#include "SettingsController.h"

SettingsController::SettingsController()
{
    controlsSettingsActive = false;
    windowSettingsActive = false;
    windowLoadSettings();
}

//------------- UI EVENTS ---------------//

/*
 * opens instructions for controls
*/
void SettingsController::controlsEvent() {
    const ImVec4 color = ImVec4(1, 0, 0, 1);

    if (ImGui::Begin("Controls"))
    {
        if (ImGui::BeginTable("Controls", 1))
        {
            ImGui::SetWindowSize(ImVec2(200, 363));
            ImGui::TableNextColumn(); ImGui::Text("Move Forward:"); ImGui::TextColored(color,"W");
            ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Text("Move Backward:"); ImGui::TextColored(color, "S");
            ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Text("Move Right"); ImGui::TextColored(color, "A");
            ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Text("Move Left:"); ImGui::TextColored(color, "D");
            ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Text("Move Upwards:"); ImGui::TextColored(color, "SPACE");
            ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Text("Move Downwards:"); ImGui::TextColored(color, "SHIFT");
            ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Text("Show/Hide Cursor:"); ImGui::TextColored(color, "LEFT CTRL");
            ImGui::Separator();
            // ImGui::TableNextColumn(); ImGui::Text("Zoom:"); ImGui::TextColored(color, "SCROLL WHEEL");
            // ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::Text("Exit:"); ImGui::TextColored(color, "ESCAPE");
            ImGui::Separator();

            ImGui::EndTable();
        }
        /* 
        * MAYBE ADD WAY FOR USER TO CHANGE CONTROLS
        if (ImGui::Button("Save")) { 
            
            setControlsSettingsActive(false); 
        }
        */
        if (ImGui::Button("Close")) { setControlsSettingsActive(false); }
    }
    ImGui::End();
}


/*
 * opens a "settings" window for the size of the application window.
*/
void SettingsController::windowEvent(GLFWwindow *window) {

    if (ImGui::Begin("Window Settings"))
    {
        ImGui::SetWindowSize(ImVec2(200, 135));
        static int xSize = windowSettings.at(0);
        static int ySize = windowSettings.at(1);
        if (ImGui::BeginTable("Window Size", 1))
        {
            ImGui::TableNextColumn(); ImGui::InputInt("X", &xSize);
            ImGui::Separator();
            ImGui::TableNextColumn(); ImGui::InputInt("Y", &ySize);
            ImGui::Separator();
            ImGui::EndTable();
        }
        if (ImGui::Button("Save")) { 
            windowSaveSettings(xSize, ySize);  
            setWindowSettingsActive(false); 
            glfwSetWindowSize(window, xSize, ySize); 
            glViewport(0, 0, xSize, ySize);
        }
        if (ImGui::Button("Close")) { setWindowSettingsActive(false); }
    }
    ImGui::End();
}


//--------------------- save/load data ----------------------//

void SettingsController::windowSaveSettings(int x, int y) {
    std::ofstream myfile("window.txt", std::ofstream::out); 
    if (myfile.is_open()) {
        myfile << x << "," << y << std::endl;
        myfile.close();
        windowSettings.at(0) = x;
        windowSettings.at(1) = y;
    }
    else {
        std::cerr << "Error opening the file!" << std::endl;
    }
}


void SettingsController::windowLoadSettings() {

    std::ifstream inputFile("window.txt");
    // Check if the file is successfully opened 
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        windowSettings.at(0) = 1280;
        windowSettings.at(1) = 720;
        return;
    }

    std::string line;
    getline(inputFile, line);
    inputFile.close();

    std::stringstream ss (line);
    std::string item;
    int i = 0;
    windowSettings.resize(2);
    while (getline(ss, item, ',')) {
        windowSettings.at(i) = std::stoi(item);
        i++;
    }
}



//--------------------- Helper Methods used for state management of ui ----------------------//
void SettingsController::setControlsSettingsActive(bool active) { controlsSettingsActive = active; }
void SettingsController::setWindowSettingsActive(bool active) { windowSettingsActive = active; }
bool SettingsController::getControlsSettingsActive() { return controlsSettingsActive; }
bool SettingsController::getWindowSettingsActive() { return windowSettingsActive; }
std::vector<int> SettingsController::getWindowSettings() { return windowSettings; } // returns the resolution of the window in a vector size of 2.
