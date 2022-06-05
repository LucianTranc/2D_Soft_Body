#pragma once
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <vector>
#include <math.h>
#include <OpenGL/gl3.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp" 
using glm::mat4;
using glm::vec2;
using glm::vec3;
using glm::radians;
using std::vector;

 
class Line {
private:
    vector<float> vertices;
    vec2 startPoint;
    vec2 endPoint;
    mat4 MVP = mat4(1.0);
    vec3 lineColor;
    Shader * shader;
    VertexArray * va;
    VertexBuffer * vb;
    VertexBufferLayout * layout;

public:

    Line(float startx, float starty, float endx, float endy);
    int setColor(vec3 color);
    int draw();
    void update(float startx, float starty, float endx, float endy, vec3 color);
};