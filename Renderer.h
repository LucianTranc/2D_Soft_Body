#pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <iostream>
#include <signal.h>
#include "VertexArray.h"
#include "Shader.h"

class IndexBuffer;

//stop program if x is false
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
//this is meant for OpenGL function calls. first GLClearError is run, then the function specified
//afterwards GLLogCall checks for errors in the function that was called. these are printed and then ASSERT
//ends the program if there are any issues
#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawLine(const VertexArray& va, const Shader& shader) const;
    void Clear() const;
    void SetClearColour(float, float, float, float);

private:
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 0.0f;
};
