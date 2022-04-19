#pragma once
#define GL_SILENCE_DEPRECATION
#include "Renderer.h"
#include <signal.h>

class VertexBuffer {
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};