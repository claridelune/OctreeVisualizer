#include "model.h"

Model::Model() {}

void Model::render(Shader shader, GLenum primitiveType) {
	mesh.render(shader, primitiveType);
}

void Model::cleanup() {
	mesh.cleanup();
}
