#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "camera.h"

#include "HelixRenderer.h"
#include "ResourceManager.h"
// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices[] = {
    // positions          // normals          
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


// world space positions of our cubes
glm::vec3 positions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};
HelixRenderer::HelixRenderer(std::string& sequence, unsigned int width, unsigned int height) {
    this->HelixShader = ResourceManager::LoadShader("helix.vs", "helix.fs", nullptr, "helix");
    this->LightShader = ResourceManager::LoadShader("light.vs", "light.fs", nullptr, "light");

    SCRHEIGHT = height;
    SCRWIDTH = width;

    sequenceLength = sequence.length();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}


void HelixRenderer::RenderHelix(Camera& camera) {
    this->HelixShader.Use();
    this->HelixShader.SetVector3f("light.direction", -0.2f, -1.0f, -0.3f);
    this->HelixShader.SetVector3f("viewPos", camera.Position);
    // light properties
    this->HelixShader.SetVector3f("light.ambient", 0.2f, 0.2f, 0.2f);
    this->HelixShader.SetVector3f("light.diffuse", 0.5f, 0.5f, 0.5f);
    this->HelixShader.SetVector3f("light.specular", 1.0f, 1.0f, 1.0f);
    // colors
    this->HelixShader.SetVector3f("objectColor", 1.0f, 0.5f, 0.31f);
    this->HelixShader.SetVector3f("lightColor", 1.0f, 1.0f, 1.0f);


    // material properties
    this->HelixShader.SetFloat("material.shininess", 32.0f);
    
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCRWIDTH/(float) SCRHEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    this->HelixShader.SetMatrix4("projection", projection);
    this->HelixShader.SetMatrix4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    this->HelixShader.SetMatrix4("model", model);

    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, positions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        this->HelixShader.SetMatrix4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}


	// while (currentIndex < sequenceLength)
	//    drawNucleotide(position, char nucleotide)
	//	  currentIndex
void HelixRenderer::DrawNucleotide(glm::vec3 position, glm::vec3 color, char nucleotide) {
}

