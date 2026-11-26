#pragma once
#include "blackHole.hpp"
#include <glad/gl.h>

GLuint compileShader(GLenum type, const char* path);
GLuint createShaderProgram();
void initRender();
void drawCircle(float x, float y, float radius, float r, float g, float b, float a);
void render(const BlackHole& blackHole);