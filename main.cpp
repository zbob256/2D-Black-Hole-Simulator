#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "render.hpp"
#include "blackHole.hpp"

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Black Hole Simulator", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc) glfwGetProcAddress)) {
        std::cout << "Failed to load OpenGL\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);

    BlackHole SagittariusA{0, 0, 0.1}; // chang to 12e6

    initRender();
    
    while (!glfwWindowShouldClose(window)) {
        render(SagittariusA);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}