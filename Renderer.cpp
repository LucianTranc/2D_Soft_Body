#include "Renderer.h"
#include "IndexBuffer.h"

//clears the error list
void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

//prints all OpenGl errors created by the function call
bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout<<"[OpenGL Error] ("<<error<<"): "<<function<<" "<<file<<": "<<line<<std::endl;
        return false;
    }
    return true;
}

//bind needed OpenGL structures and make a draw call
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
} 

void Renderer::DrawLine(const VertexArray& va, const Shader& shader) const
{
    shader.Bind();
    va.Bind();

    GLCall(glDrawArrays(GL_LINES, 0, 2););
} 

void Renderer::Clear() const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetClearColour(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}
