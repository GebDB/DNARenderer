
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


HelixRenderer::HelixRenderer(std::string& sequence, unsigned int width, unsigned int height) {
    this->HelixShader = ResourceManager::LoadShader("helix.vs", "helix.fs", nullptr, "helix");
    this->LightShader = ResourceManager::LoadShader("light.vs", "light.fs", nullptr, "light");



    SCRHEIGHT = height;
    SCRWIDTH = width;

    sequenceLength = sequence.length();

}


void HelixRenderer::RenderHelix(Camera& camera, Model& DNALadder, string& sequence) { // maybe change string to DNA object
    int sequenceLength = sequence.length();
    this->HelixShader.Use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCRWIDTH / (float)SCRHEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    this->HelixShader.SetMatrix4("projection", projection);
    this->HelixShader.SetMatrix4("view", view);
    
    for (int i = 0; i < sequenceLength; i++) {
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f + (float) i, 0.0f)); // each model is loaded sequentially upwards from the center
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // scale it down
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        switch (sequence.at(i)) {
            case 'A':
                this->HelixShader.SetInteger("invertColor", 0);
                break;
            case 'T':
                this->HelixShader.SetInteger("invertColor", 0);
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;

            case 'C':
                this->HelixShader.SetInteger("invertColor", 1);
                break;

            case 'G':
                this->HelixShader.SetInteger("invertColor", 1);
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
        
        }
        this->HelixShader.SetMatrix4("model", model);
        DNALadder.Draw(this->HelixShader);

    }
}


	// while (currentIndex < sequenceLength)
	//    drawNucleotide(position, char nucleotide)
	//	  currentIndex
void HelixRenderer::DrawNucleotide(glm::vec3 position, glm::vec3 color, char nucleotide) {
}

