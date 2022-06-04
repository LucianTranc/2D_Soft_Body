#include "Background.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Game.h"

Background::Background()
{
}

void Background::init()
{
    texture = Game::assetManager->GetTexture("table");
}

void Background::draw()
{
    texture->Bind();
    glm::vec3 translation(0, 0, 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 projection = glm::ortho(0.0, (double)Game::screenSize->x, (double)Game::screenSize->y, 0.0);
    glm::mat4 mvp = projection * model;
    texture->shader->Bind();
    texture->shader->SetUniformMat4f("u_MVP", mvp);
    Game::renderer->Draw(*(texture->va), *(texture->ib), *(texture->shader));
}