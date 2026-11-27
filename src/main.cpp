#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "render.hpp"
#include "blackHole.hpp"
#include "config.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    collectJSON();

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "2D Black Hole Simulator", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    GLFWimage icon;
    icon.pixels = stbi_load(ASSET_DIR "/icon.png", &icon.width, &icon.height, nullptr, 4);

    if (icon.pixels) {
        glfwSetWindowIcon(window, 1, &icon);
        stbi_image_free(icon.pixels);
    }
    else {
        std::cerr << "Failed to load window icon: "
                << stbi_failure_reason() << '\n';
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc) glfwGetProcAddress)) {
        std::cout << "Failed to load OpenGL\n";
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);

    glViewport(0, 0, WIDTH, HEIGHT);

    long double SagAr_s = 4.3e6L * SOLAR_MASS; // make all this from BHDjson
    long double sagAr_sProp = SagAr_s / UNIVERSE_SIZE;
    BlackHole SagittariusA{0.f, 0, sagAr_sProp};

    std::vector blackHoles = {SagittariusA};

    initRender();
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);


        for (BlackHole &blackHole : blackHoles) {
            render(blackHole);
        }

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