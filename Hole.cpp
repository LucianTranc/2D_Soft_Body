#include "Hole.h"
#include "Game.h"

//initialize variables
Hole::Hole(float posx, float posy, float r) {

    position.x = posx;
    position.y = posy;
    radius = r;

    texPos.x = position.x - radius;
	texPos.y = position.y - radius;

    texture = Game::assetManager->GetTexture("ball3");

}
//print the position of the hole
void Hole::printHole() {
    std::cout<<"Hole"<<std::endl;
    std::cout<<position.x<<std::endl;
    std::cout<<position.y<<std::endl;
}

void Hole::draw() {

    Game::assetManager->SetActiveTexture("ball3");
    glm::vec3 translation(texPos.x, texPos.y, 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 projection = glm::ortho(0.0, 1270.0, 670.0, 0.0);
    glm::mat4 mvp = projection * model;
    texture->shader->Bind();
    texture->shader->SetUniformMat4f("u_MVP", mvp);
    Game::renderer->Draw(*(texture->va), *(texture->ib), *(texture->shader));
}
