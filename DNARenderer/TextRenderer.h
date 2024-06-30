#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <iostream>
#include <map>
#include <string>

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class TextRenderer
{
public:
    // holds precompiled characters
    std::map<GLchar, Character> Characters;

    Shader TextShader;
    TextRenderer(unsigned int width, unsigned int height);
    void Load(std::string font, unsigned int fontSize);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
    void AdjustProjection(int width, int height);
private:
    unsigned int VAO, VBO;
};
#endif




