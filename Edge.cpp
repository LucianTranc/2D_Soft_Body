#include "Edge.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Game.h"

//initialize variables
Edge::Edge(float pos1x, float pos1y, float pos2x, float pos2y, float r) {

    position1.x = pos1x;
    position1.y = pos1y;
    position2.x = pos2x;
    position2.y = pos2y;
    radius = r;

    texPos1.x = position1.x - radius;
	texPos1.y = position1.y - radius;
    texPos2.x = position2.x - radius;
	texPos2.y = position2.y - radius;

    texture = Game::assetManager->GetTexture("ball2");

}


void Edge::draw() {

    //a draw call for each texPos
    {
        texture->Bind();
        glm::vec3 translation(texPos1.x, texPos1.y, 0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 projection = glm::ortho(0.0, 1270.0, 670.0, 0.0);
        glm::mat4 mvp = projection * model;
        texture->shader->Bind();
        texture->shader->SetUniformMat4f("u_MVP", mvp);
        Game::renderer->Draw(*(texture->va), *(texture->ib), *(texture->shader));
    }

    {
        texture->Bind();
        glm::vec3 translation(texPos2.x, texPos2.y, 0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 projection = glm::ortho(0.0, 1270.0, 670.0, 0.0);
        glm::mat4 mvp = projection * model;
        texture->shader->Bind();
        texture->shader->SetUniformMat4f("u_MVP", mvp);
        Game::renderer->Draw(*(texture->va), *(texture->ib), *(texture->shader));
    }

    /* float nx = -(position1.y - position2.y);
	float ny = (position1.x - position2.x);
	float d = sqrt(nx*nx + ny * ny);
	nx /= d;
	ny /= d;
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(Game::renderer, position1.x + nx * radius, position1.y + ny * radius, position2.x + nx * radius, position2.y + ny * radius);
    SDL_RenderDrawLine(Game::renderer, position1.x - nx * radius, position1.y - ny * radius, position2.x - nx * radius, position2.y - ny * radius);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255); */

}

void Edge::update() {
    
    
}