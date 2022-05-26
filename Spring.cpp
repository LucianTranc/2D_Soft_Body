#include "Spring.h"
#include "Game.h"

//initialize variables
Spring::Spring(float pos1x, float pos1y, float pos2x, float pos2y) {

    std::cout<<"1"<<std::endl;

    position1.x = pos1x;
    position1.y = pos1y;
    position2.x = pos2x;
    position2.y = pos2y;

    float positions[] = {
        position1.x, position1.y,
        position2.x, position2.y,
    };

    std::cout<<"2"<<std::endl;


    shader = new Shader("shaders/line.shader");

    va = new VertexArray();

    vb = new VertexBuffer(positions, 4 * sizeof(float));

	VertexBufferLayout * layout = new VertexBufferLayout();

    std::cout<<"3"<<std::endl;


    layout->Push<float>(2);
    va->AddBuffer(*vb, *layout);

    //glm::mat4 proj = glm::ortho(0.0f, 1270.0f, 670.0f, 0.0f);

    shader->Bind();
    //shader->SetUniformMat4f("MVP", proj);

    std::cout<<"4"<<std::endl;

    
    va->Unbind();
    vb->Unbind();
    shader->Unbind();

    std::cout<<"5"<<std::endl;

}

//print the position of the spring
void Spring::printSpring() {
    std::cout<<"Spring"<<std::endl;
    std::cout<<position1.x<<std::endl;
    std::cout<<position1.y<<std::endl;
    std::cout<<position2.x<<std::endl;
    std::cout<<position2.y<<std::endl;
}

void Spring::draw() {

    std::cout<<"6"<<std::endl;


    glm::vec3 translation(0, 0, 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
    model = glm::scale(model, glm::vec3(1.0f));
    glm::mat4 projection = glm::ortho(0.0, 1270.0, 670.0, 0.0);
    glm::mat4 mvp = projection * model;

    std::cout<<"7"<<std::endl;


    shader->SetUniformMat4f("MVP", mvp);
    shader->Bind();

    std::cout<<"8"<<std::endl;


    // Draw the line
    //glDrawArrays(GL_LINES, 0, 2);
    Game::renderer->DrawLine(*(va), *(shader));

    std::cout<<"9"<<std::endl;


    // need to give the spring a shader

    /* Ball.draw()

    if (texture) {
        texture->Bind();
        glm::vec3 translation(texPos.x, texPos.y, 0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        model = glm::scale(model, glm::vec3(1.0f));
        glm::mat4 projection = glm::ortho(0.0, 1270.0, 670.0, 0.0);
        glm::mat4 mvp = projection * model;
        texture->shader->Bind();
        texture->shader->SetUniformMat4f("u_MVP", mvp);
        Game::renderer->Draw(*(texture->va), *(texture->ib), *(texture->shader));
    }
    */

}
