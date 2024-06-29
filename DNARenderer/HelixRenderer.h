#ifndef HELIXRENDERER_H
#define HELIXRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>
#include <ImGUI/imgui_stdlib.h>

#include "shader.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "camera.h"
#include "model.h"

#include "HelixRenderer.h"
#include "ResourceManager.h"


class HelixRenderer
{
public:
    HelixRenderer(unsigned int width, unsigned int height);
    ~HelixRenderer();
    void RenderHelix(Camera& camera, Model& DNALadder, Model& backbone, std::string sequence, float scale, bool rotationToggled);
    bool isInvalidInput();
private:
    unsigned int VAO, lightVAO, VBO, EBO, sequenceLength, SCRWIDTH, SCRHEIGHT;
    Shader HelixShader, LightShader, BackboneShader;
    string sequence;
    bool invalidInput;
};
#endif




