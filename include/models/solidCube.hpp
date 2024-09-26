#ifndef SOLID_CUBE_H
#define SOLID_CUBE_H

#include "model.h"

class SolidCube : public Model {
public:
    glm::vec3 pos;
    glm::vec3 size;
    glm::vec3 color;

    SolidCube(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f))
        : pos(pos), size(size), color(color) {}

    void init() {
        int noVertices = 36;

        float vertices[] = {
            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f, 
             0.5f,  0.5f, -0.5f, 
             0.5f,  0.5f, -0.5f, 
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f, -0.5f,  0.5f, 
             0.5f, -0.5f,  0.5f, 
             0.5f,  0.5f,  0.5f, 
             0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f, 

            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 

             0.5f,  0.5f,  0.5f, 
             0.5f,  0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f,  0.5f, 
             0.5f,  0.5f,  0.5f, 

            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f,  0.5f, 
             0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f,  0.5f, -0.5f, 
             0.5f,  0.5f, -0.5f, 
              0.5f,  0.5f,  0.5f, 
             0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f 
        };

        std::vector<unsigned int> indices(noVertices);
        for (unsigned int i = 0; i < noVertices; i++) {
            indices[i] = i;
        }

        mesh = Mesh(Vertex::genList(vertices, noVertices), indices);
    }

    void render(Shader shader) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, size);
        shader.setMat4("model", model);

        shader.setVec3("color", color);

        Model::render(shader);
    }
};

#endif
