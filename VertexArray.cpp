#include "VertexArray.h"
#include "Renderer.h"
#include <stdint.h>
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

#define INT2VOIDP(i) (void*)(uintptr_t)(i)

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);

}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {

    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), INT2VOIDP(offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}