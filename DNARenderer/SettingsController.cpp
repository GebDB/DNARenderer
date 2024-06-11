#include "SettingsController.h"

SettingsController::SettingsController()
{
    controlsSettingsActive = false;
    inputSizeSettingsActive = false;
    windowSettingsActive = false;
}

void SettingsController::controlsEvent() {
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Controls"))
    {
        if (ImGui::Button("Save")) { setControlsSettingsActive(false); }
        if (ImGui::Button("Close")) { setControlsSettingsActive(false); }
    }
    ImGui::End();
}

void SettingsController::inputSizeEvent() {
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Input Size"))
    {
        if (ImGui::Button("Save")) { setInputSizeSettingsActive(false); }
        if (ImGui::Button("Close")) { setInputSizeSettingsActive(false); }
    }
    ImGui::End();
}

void SettingsController::windowEvent() {
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Window Settings"))
    {
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