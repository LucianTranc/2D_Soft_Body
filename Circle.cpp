#include "Circle.h"
#include "Game.h"

Circle::Circle(float startx, float starty, float r)
{
    position = vec2(startx, starty);
    radius = r;

    float vertices[] = {
        // positions       
         0+radius, 0+radius, 0.0f,
         0+radius, 0-radius, 0.0f,
         0-radius, 0-radius, 0.0f,
         0-radius, 0+radius, 0.0f,
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    shader = Game::assetManager->GetShader("circle");

    va = new VertexArray();
    vb = new VertexBuffer(vertices, 12 * sizeof(float));
	layout = new VertexBufferLayout();
    layout->Push<float>(3);
    va->AddBuffer(*vb, *layout);
    ib = new IndexBuffer(indices, 6);

    shader->Unbind();
    va->Unbind();
    vb->Unbind();
    ib->Unbind();

    glm::vec3 translation(position.x, position.y, 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 projection = glm::ortho(0.0, (double)Game::screenSize->x, (double)Game::screenSize->y, 0.0);
    MVP = projection * model;
}

int Circle::setColor(vec3 newcolor)
{
    color = newcolor;
    return 1;
}

int Circle::draw()
{
    shader->Bind();
    
    glUniformMatrix4fv(glGetUniformLocation(shader->m_RendererID, "MVP"), 1, GL_FALSE, &MVP[0][0]);

    glm::vec3 col = glm::vec3(0.0f, 0.0f, 0.0f);
    glUniform3fv(glGetUniformLocation(shader->m_RendererID, "color"), 1, glm::value_ptr(col));

    glm::vec2 res = glm::vec2(Game::screenSize->x, Game::screenSize->y);
    glUniform2fv(glGetUniformLocation(shader->m_RendererID, "resolution"), 1, glm::value_ptr(res));

    glm::vec2 centerPos = glm::vec2(position.x, Game::screenSize->y - position.y);
    glUniform2fv(glGetUniformLocation(shader->m_RendererID, "center"), 1, glm::value_ptr(centerPos));

    glUniform1f(glGetUniformLocation(shader->m_RendererID,"uRadius"), radius);

    shader->Bind();
    ib->Bind();
    va->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 1;

}

void Circle::update(float startx, float starty, float r)
{
    position = vec2(startx, starty);
    radius = r;

    glm::vec3 translation(position.x, position.y, 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 projection = glm::ortho(0.0, (double)Game::screenSize->x, (double)Game::screenSize->y, 0.0);
    MVP = projection * model;

}