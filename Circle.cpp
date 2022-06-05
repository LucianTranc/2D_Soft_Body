#include "Circle.h"
#include "Game.h"

Circle::Circle(float startx, float starty, float r) {

    std::cout<<"creating circle"<<std::endl;

    position = vec2(startx, starty);
    radius = r;

    float vertices[] = {
        // positions       
         position.x+radius, position.y+radius, 0.0f,
         position.x+radius, position.y-radius, 0.0f,
         position.x-radius, position.y-radius, 0.0f,
         position.x-radius, position.y+radius, 0.0f,
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

	shader = Game::assetManager->GetShader("circle");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	shader->Bind();

    MVP = glm::ortho(0.0f, Game::screenSize->x, Game::screenSize->y, 0.0f);

}

int Circle::setColor(vec3 newcolor) {
    color = newcolor;
    return 1;
}

int Circle::draw() {

    shader->Bind();

    glUniformMatrix4fv(glGetUniformLocation(shader->m_RendererID, "MVP"), 1, GL_FALSE, &MVP[0][0]);

    glm::vec3 col = glm::vec3(1.0f, 0.1f, 0.1f);
    glUniform3fv(glGetUniformLocation(shader->m_RendererID, "color"), 1, glm::value_ptr(col));

    glm::vec2 res = glm::vec2(Game::screenSize->x, Game::screenSize->y);
    glUniform2fv(glGetUniformLocation(shader->m_RendererID, "resolution"), 1, glm::value_ptr(res));

    glm::vec2 centerPos = glm::vec2(position.x, Game::screenSize->y - position.y);
    glUniform2fv(glGetUniformLocation(shader->m_RendererID, "center"), 1, glm::value_ptr(centerPos));

    glUniform1f(glGetUniformLocation(shader->m_RendererID,"uRadius"), radius);

    shader->Bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



    return 1;
}
