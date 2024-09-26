#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

#include "shader.h"

struct Vertex {
    glm::vec3 pos;

    static std::vector<Vertex> genList(float* vertices, int noVertices);
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO;

    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void render(Shader shader, GLenum primitiveType = GL_TRIANGLES);

    void cleanup();

private:
    unsigned int VBO, EBO;

    void setup();
};

#endif
