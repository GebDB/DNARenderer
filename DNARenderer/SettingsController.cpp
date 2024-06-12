#include "SettingsController.h"

SettingsController::SettingsController()
{
    controlsSettingsActive = false;
    inputSizeSettingsActive = false;
    windowSettingsActive = false;
}

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

void SettingsController::inputSizeEvent() {

    if (ImGui::Begin("Input Size"))
    {
        static int inputSize = 8000000;
        ImGui::SetWindowSize(ImVec2(234, 108));
        if (ImGui::BeginTable("Input Size", 1))
        {
            static int xSize = 1280;
            ImGui::TableNextColumn(); ImGui::InputInt("Input Size", &inputSize);
            ImGui::Separator();
            ImGui::EndTable();
        }
        if (ImGui::Button("Save")) { setInputSizeSettingsActive(false); }
        if (ImGui::Button("Close")) { setInputSizeSettingsActive(false); }
    }
    ImGui::End();
}

void SettingsController::windowEvent() {

    if (ImGui::Begin("Window Settings"))
    {
        ImGui::SetWindowSize(ImVec2(200, 135));
        if (ImGui::BeginTable("Window Size", 1))
        {
            static int xSize = 1080;
            ImGui::TableNextColumn(); ImGui::InputInt("X", &xSize);
            ImGui::Separator();
            static int ySize = 720;
            ImGui::TableNextColumn(); ImGui::InputInt("Y", &ySize);
            ImGui::Separator();
            ImGui::EndTable();
        }
        if (ImGui::Button("Save")) { setWindowSettingsActive(false); }
        if (ImGui::Button("Close")) { setWindowSettingsActive(false); }
    }
    ImGui::End();
}

void SettingsController::setControlsSettingsActive(bool active) { controlsSettingsActive = active; }
void SettingsController::setWindowSettingsActive(bool active) { windowSettingsActive = active; }
void SettingsController::setInputSizeSettingsActive(bool active) { inputSizeSettingsActive = active; }
bool SettingsController::getControlsSettingsActive() { return controlsSettingsActive; }
bool SettingsController::getWindowSettingsActive() { return windowSettingsActive; }
bool SettingsController::getInputSizeSettingsActive() { return inputSizeSettingsActive; }