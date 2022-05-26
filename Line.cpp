#include "Line.h"
#include "Game.h"

Line::Line(float startx, float starty, float endx, float endy) {

    startPoint = vec2(startx, starty);
    endPoint = vec2(endx, endy);
    lineColor = vec3(0,0,0);

    float positions[] = {
        startx, starty,
        endx, endy,
    };
    
    shader = Game::assetManager->GetShader("line");

    va = new VertexArray();
    vb = new VertexBuffer(positions, 4 * sizeof(float));
	layout = new VertexBufferLayout();
    layout->Push<float>(2);
    va->AddBuffer(*vb, *layout);

    shader->Unbind();
    va->Unbind();
    vb->Unbind();

    MVP = glm::ortho(0.0f, 1270.0f, 670.0f, 0.0f);

}

int Line::setColor(vec3 color) {
    lineColor = color;
    return 1;
}

int Line::draw() {
    shader->Bind();

    glUniformMatrix4fv(glGetUniformLocation(shader->m_RendererID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniform3fv(glGetUniformLocation(shader->m_RendererID, "color"), 1, &lineColor[0]);

    va->Bind();
    glDrawArrays(GL_LINES, 0, 2);
    return 1;
}

void Line::update(float startx, float starty, float endx, float endy) {

    startPoint = vec2(startx, starty);
    endPoint = vec2(endx, endy);

    float positions[] = {
        startx, starty,
        endx, endy,
    };

    vb->UpdateBuffer(positions, 4 * sizeof(float));
    
}
