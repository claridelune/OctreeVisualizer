#ifndef WIREFRAME_CUBE_H
#define WIREFRAME_CUBE_H

#include "model.h"

class WireframeCube : public Model {
public:
    glm::vec3 pos;
    glm::vec3 size;
    glm::vec3 color;

    WireframeCube(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 color = glm::vec3(0.5f))
        : pos(pos), size(size), color(color) {}

    void init() {
        int noVertices = 8;
        
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f
        };

        unsigned int indices[] = {
            0, 1,
            1, 2,
            2, 3,
            3, 0,

            4, 5,
            5, 6,
            6, 7,
            7, 4,

            0, 4,
            1, 5,
            2, 6,
            3, 7
        };

        std::vector<unsigned int> indicesVec(indices, indices + 24);
        mesh = Mesh(Vertex::genList(vertices, noVertices), indicesVec);
    }

    void render(Shader shader) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, size);
        shader.setMat4("model", model);

        shader.setVec3("color", color);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        Model::render(shader, GL_LINES);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
};

#endif

