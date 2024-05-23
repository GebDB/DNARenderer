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


class HelixRenderer
{
public:
    HelixRenderer(std::string& sequence, unsigned int width, unsigned int height);
    ~HelixRenderer();
    void RenderHelix(Camera& camera);
    void DrawNucleotide(glm::vec3 position, glm::vec3 color, char nucleotide);
private:
    unsigned int VAO, lightVAO, VBO, EBO, sequenceLength, SCRWIDTH, SCRHEIGHT;

    Shader HelixShader, LightShader;

};
#endif




