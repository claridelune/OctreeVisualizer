#include <iostream>
#include <vector>
#include <string>

#include "octree.h"
#include "pointProcessor.h"

#include "screen.h"
#include "shader.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"

#include "models/wireframeCube.hpp"
#include "models/solidCube.hpp"


void processInput(double dt);
void renderOctree(Octree* node, Shader shader, WireframeCube& octantTemplate, SolidCube& pointTemplate);


Screen screen;
Camera Camera::defaultCamera(glm::vec3(0.0f, 0.0f, 270.0f));

double deltaTime = 0.0f;
double lastFrame = 0.0f;

int main()
{
    // Octree --------------------------------
    PointProcessor pp("data/points3.csv");
    if (!pp.processFile()) {
        return -1;
    }
    
    std::vector<Point> points = pp.getPoints();
    // pp.printBounds();

    Octree tree(pp.getBottomLeft(), pp.getH(), 60);

    for (auto& p : points) {
        tree.insert(p);
    }

    // OPENGL ----------------------------------

    glfwInit();   
    // version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core profile(modern functions)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!screen.init()) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
        
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
      return -1;
    }

    screen.setParameters();
    // SHADERS ----------------------------------
	Shader shader("assets/vertex_core.shader", "assets/fragment_core.shader");

	// MODELS ----------------------------------
    WireframeCube octantCubeTemplate;
    octantCubeTemplate.init();

    SolidCube pointCubeTemplate;
    pointCubeTemplate.init();
    while (!screen.shouldClose()) {

        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        processInput(deltaTime);

        // render
        screen.update();

        // activate shader
        shader.activate();

        // Set the view and projection matrices
        glm::mat4 view = Camera::defaultCamera.getViewMatrix();
        glm::mat4 projection = glm::perspective(
            glm::radians(Camera::defaultCamera.zoom), 
            (float)Screen::SCR_WIDTH / (float)Screen::SCR_HEIGHT, 0.1f, 300.0f);
        
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // render the Octree
        renderOctree(&tree, shader, octantCubeTemplate, pointCubeTemplate);

        // Swap buffers and poll events
        screen.newFrame();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(double dt) {
    if (Keyboard::key(GLFW_KEY_ESCAPE)) {
        screen.setShouldClose(true);
	}

	if (Keyboard::key(GLFW_KEY_UP)) {
	}
	if (Keyboard::key(GLFW_KEY_DOWN)) {
	}

	// move camera
	if (Keyboard::key(GLFW_KEY_W)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::FORWARD, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::BACKWARD, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::RIGHT, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_A)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::LEFT, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_SPACE)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::UP, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::DOWN, deltaTime);
	}
    Camera::defaultCamera.updateCameraDirection(Mouse::getDX(), Mouse::getDY());
}

void renderOctree(Octree* node, Shader shader, WireframeCube& octantTemplate, SolidCube& pointTemplate) {
    if (!node) return;

    octantTemplate.pos = glm::vec3(node->getBottomLeft().x + node->getH()/2, 
                                       node->getBottomLeft().y + node->getH()/2, 
                                       node->getBottomLeft().z + node->getH()/2);
    octantTemplate.size = glm::vec3(node->getH());
    octantTemplate.render(shader);

    for (auto point : node->points) {
        pointTemplate.pos = glm::vec3(point->x, point->y, point->z);
        pointTemplate.size = glm::vec3(0.5f);
        pointTemplate.render(shader);
    }

    for (int i = 0; i < 8; i++) {
        if (node->children[i]) {
            renderOctree(node->children[i], shader, octantTemplate, pointTemplate);
        }
    }
}
