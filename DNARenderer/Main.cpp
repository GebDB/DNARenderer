#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>
#include <ImGUI/imgui_stdlib.h>

#include "TextRenderer.h"
#include "HelixRenderer.h"

#include "ResourceManager.h"
#include "SettingsController.h"

#include <camera.h>

#include <DNA.h>

/** CHECKLIST 
- add controls settings
- set sequence button is cut off screen when window settings is a smalller number, fix?
**/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

// Settings
SettingsController settings;
unsigned int SCREEN_WIDTH = settings.getWindowSettings().at(0);
unsigned int SCREEN_HEIGHT = settings.getWindowSettings().at(1);
// left control toggle
bool ctrlToggled = false;

// camera
Camera camera(glm::vec3(0.0f, 20.0f, 60.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
float scale = 1.0;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// The DNA sequence that will be displayed in the application.
DNA dna;
TextRenderer* Text;
HelixRenderer* Helix;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DNA Sim", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Set up Text Renderer
    Text = new TextRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    Text->Load("assets/fonts/AovelSansRounded-rdDL.ttf", 24);

    std::string seq = "ATCCGGTTGCTGGGTGAACTCCAGACTCGGGGCGACAACTC";
    dna.setSequence(seq);


    // Set up Helix Renderer
    Helix = new HelixRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    //Load model
    Model DNALadder("assets/objects/DNALadder/DNApair1.obj");
    Model backbone("assets/objects/PhosphateBackbone/backbone1.obj");

    // ImGUI initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // render loop
    // -----------
    std::string sequenceInput = "";
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.165, 0.165, 0.2, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Helix->RenderHelix(camera, DNALadder, backbone, dna.getSequence(), 1/scale);
        // clear depth and render text in the forefront. 
        glClear(GL_DEPTH_BUFFER_BIT);
        Text->RenderText("Sequence: " + dna.getSequence(), 15.0f, SCREEN_HEIGHT - 30.0f, 1.0f);

        // -------------- All ImGUI implementation here ----------------//
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //  Main Menu Bar implementation 
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Settings"))
            {
                if (ImGui::MenuItem("Controls")) { settings.setControlsSettingsActive(true); }
                if (ImGui::MenuItem("Window")) { settings.setWindowSettingsActive(true); }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Import DNA Sequence")) {}
                if (ImGui::MenuItem("Save DNA Sequence")) {}
                if (ImGui::MenuItem("Delete DNA Sequence")) {}
                ImGui::EndMenu();
            }
            if (ImGui::Button("Reset")) {
                dna.setSequence("");
            }
            ImGui::Text("Sequence Input:");
            ImGui::InputText("", &sequenceInput);
            if (ImGui::Button("Set Sequence")) {
                dna.setSequence(sequenceInput);
            }

            ImGui::EndMainMenuBar();
        }
        if (settings.getControlsSettingsActive()) {
            settings.controlsEvent();
        }
        if (settings.getWindowSettingsActive()) {
            settings.windowEvent(window);
        }

        // 2 sliders for movement speed and camera zoom.
        if (ImGui::Begin("Scale and Movement Speed")) {
            ImGui::SetWindowSize(ImVec2(355, 78)); 
            ImGui::SetWindowPos(ImVec2(10, 28));
            if (ImGui::SliderFloat("Scale", &scale, 0.25f, 10.0f)) {}
            if (ImGui::SliderFloat("Movement Speed", &camera.MovementSpeed, 0.5f, 500.0f)) {}
            if (!ctrlToggled)
            {
                    ImGui::SetWindowSize(ImVec2(355, 94));
                    ImGui::Text("Press left-ctrl to show cursor");

            }

        }
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();

    ImGui_ImplOpenGL3_Shutdown();
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !ctrlToggled)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !ctrlToggled)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !ctrlToggled)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !ctrlToggled)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !ctrlToggled)
        camera.ProcessKeyboard(MOVEUP, deltaTime);
    if ((glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) && !ctrlToggled)
        camera.ProcessKeyboard(MOVEDOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (!ctrlToggled) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }
    else {
        firstMouse = true;
    }
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
    {
        switch (ctrlToggled) {
        case true:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            ctrlToggled = false;
            break;
        case false:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            ctrlToggled = true;
            break;
        }

    }
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
/* Not needed as zooming will be handled by scaling in the ui.
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}*/