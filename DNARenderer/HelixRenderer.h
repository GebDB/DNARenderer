#ifndef HELIXRENDERER_H
#define HELIXRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "camera.h"
#include "model.h"


class HelixRenderer
{
public:
    HelixRenderer(std::string& sequence, unsigned int width, unsigned int height);
    ~HelixRenderer();
    void RenderHelix(Camera& camera, Model& DNALadder, Model& backbone);
private:
    unsigned int VAO, lightVAO, VBO, EBO, sequenceLength, SCRWIDTH, SCRHEIGHT;
    Shader HelixShader, LightShader, BackboneShader;
    string sequence;
};
#endif




