#include "screen.h"
#include "keyboard.h"
#include "mouse.h"
#include <GLFW/glfw3.h>

unsigned int Screen::SCR_WIDTH = 1200;
unsigned int Screen::SCR_HEIGHT = 1000;

void Screen::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

Screen::Screen() : window(nullptr) {
}

bool Screen::init() {
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TITLE", NULL, NULL);

    if (window == NULL) {
        return false;
    }

    glfwMakeContextCurrent(window);
    return true;
}

void Screen::setParameters() {
    glfwSetKeyCallback(window, Keyboard::keyCallback);
    glViewport(0, 0, SCR_HEIGHT, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, Screen::framebufferSizeCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable cursor
	glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
	glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

	glEnable(GL_DEPTH_TEST);
}

void Screen::update() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::newFrame() {
    glfwSwapBuffers(window);
}

bool Screen::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Screen::setShouldClose(bool sc) {
    glfwSetWindowShouldClose(window, sc);
}

GLFWwindow *Screen::getWindow() {
    return this->window;
}
