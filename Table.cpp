#include "Table.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Game.h"

Table::Table() {

}

void Table::init() {

    texture = Game::assetManager->GetTexture("table");

}

void Table::draw() {

    texture->Bind();
    glm::vec3 translation(0, 0, 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 projection = glm::ortho(0.0, 1270.0, 670.0, 0.0);
    glm::mat4 mvp = projection * model;
    texture->shader->Bind();
    texture->shader->SetUniformMat4f("u_MVP", mvp);
    Game::renderer->Draw(*(texture->va), *(texture->ib), *(texture->shader));

}