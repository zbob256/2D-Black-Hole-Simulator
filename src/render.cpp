#include "render.hpp"
#include <glad/gl.h>
#include "blackHole.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "config.hpp"

GLuint VAO, VBO;
GLuint shaderProgram;

GLuint compileShader(GLenum type, const char* path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Could not open: " << path << '\n';
        return 0;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    const char* src = source.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cout << "Shader error: " << log << '\n';
    }

    return shader;
}

GLuint createShaderProgram() {
    GLuint vertexShader = compileShader(
        GL_VERTEX_SHADER,
        SHADER_DIR "/blackHole.vert"
    );

    GLuint fragmentShader = compileShader(
        GL_FRAGMENT_SHADER,
        SHADER_DIR "/blackHole.frag"
    );

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cout << "Link error: " << log << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void initRender() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shaderProgram = createShaderProgram();
}

void drawCircle(float x, float y, float radius, float r, float g, float b, float a) {
    const int segments = 100;

    float vertices[(segments + 2) * 2];

    vertices[0] = x;
    vertices[1] = y;

    for (int i = 0; i <= segments; i++) {
        float theta = (2.0f * M_PI * i) / segments;

        vertices[(i + 1) * 2] = x + radius * cos(theta);
        vertices[(i + 1) * 2 + 1] = y + radius * sin(theta);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glUseProgram(shaderProgram);

    GLint colorLoc = glGetUniformLocation(shaderProgram, "circleColor");
    glUniform4f(colorLoc, r, g, b, a);

    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
}

void render(const BlackHole& blackHole) {
    float accretionDisk = static_cast<float>(blackHole.accretionDisk / UNIVERSE_SIZE);
    float photonSphere = static_cast<float>(blackHole.photonSphere / UNIVERSE_SIZE);
    float distance = static_cast<float>(blackHole.distance / UNIVERSE_SIZE);

    float x = distance * cos(blackHole.angle);
    float y = distance * sin(blackHole.angle);

    for (int i = 0; i < 10; i++) {
        drawCircle(x, y, accretionDisk * (1 - i / 35.f), 0.95f, 0.4f, 0.f, 0.1f + i / 10.f);
    }

    for (int i = 0; i < 5; i++) {
        drawCircle(x, y, accretionDisk * (0.8 - i / 25.f), 0.f, 0.f, 0.f, 0.5f + (i / 10.f));
    }
    
    drawCircle(x, y, photonSphere, 1.f, 1.f, 1.f, 1.f);
    drawCircle(x, y, photonSphere * 0.99, 0.f, 0.f, 0.f, 1.f);


    glBindVertexArray(0);
}