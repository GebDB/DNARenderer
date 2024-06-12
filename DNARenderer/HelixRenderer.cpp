
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "camera.h"
#include <model.h>

#include "HelixRenderer.h"
#include "ResourceManager.h"


HelixRenderer::HelixRenderer(unsigned int width, unsigned int height) {
    this->HelixShader = ResourceManager::LoadShader("helix.vs", "helix.fs", nullptr, "helix");
    this->LightShader = ResourceManager::LoadShader("light.vs", "light.fs", nullptr, "light");

    SCRHEIGHT = height;
    SCRWIDTH = width;

}


void HelixRenderer::RenderHelix(Camera& camera, Model& DNALadder, Model& backbone, string sequence, float scale) { 
    sequenceLength = sequence.length();
    int sequenceLength = sequence.length();
    this->HelixShader.Use();

    // view/projection transformations, large far-plane number.
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom) * scale, (float)SCRWIDTH / (float)SCRHEIGHT, 0.1f, 3000.0f); 
    glm::mat4 view = camera.GetViewMatrix();
    this->HelixShader.SetMatrix4("projection", projection);
    this->HelixShader.SetMatrix4("view", view);

    for (int i = 0; i < sequenceLength; i++) {
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f); // model used for base pairs
        model = glm::translate(model, glm::vec3(0.0f, 0.0f + (float)i, 0.0f)); // each model is loaded sequentially upwards from the center
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f )); // scale down
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));  // rotate each base pair to create a helix structure

        glm::mat4 rightBackbone = glm::scale(model, glm::vec3(1.003f, 0.575f, 1.0f)); // scale with base pairs.
        rightBackbone = glm::rotate(rightBackbone, glm::radians(151.1f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 leftBackbone = glm::scale(model, glm::vec3(-1.003f, 0.575f, 1.0f));
        leftBackbone = glm::rotate(leftBackbone, glm::radians(28.45f), glm::vec3(1.0f, 0.0f, 0.0f));

        switch (sequence.at(i)) {
        case 'a':
        case 'A':
            this->HelixShader.SetInteger("invertColor", 0);
            break;
        case 't':
        case 'T':
            this->HelixShader.SetInteger("invertColor", 0);
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case 'c':
        case 'C':
            this->HelixShader.SetInteger("invertColor", 1);
            break;
        case 'g':
        case 'G':
            this->HelixShader.SetInteger("invertColor", 1);
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            break;

        }
        this->HelixShader.SetMatrix4("model", model);
        DNALadder.Draw(this->HelixShader);

        this->HelixShader.SetInteger("invertColor", 0);
        this->HelixShader.SetMatrix4("model", rightBackbone);
        backbone.Draw(this->HelixShader);


        this->HelixShader.SetMatrix4("model", leftBackbone);
        backbone.Draw(this->HelixShader);
    }

}