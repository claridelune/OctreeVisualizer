#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "mesh.h"

class Model {
public:
	Mesh mesh;

	Model();

	void init();

	void render(Shader shader, GLenum primitiveType = GL_TRIANGLES);

	void cleanup();
};

#endif
