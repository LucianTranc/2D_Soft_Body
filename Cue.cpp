#include "Cue.h"
#include "Game.h"

Cue::Cue() {

    texture = Game::assetManager->GetTexture("cue");

}

void Cue::draw() {

    //if the balls are not moving then update the values of mouseangle and texPos
    //we do not want the cue to move relative to the cue ball right after a hit
    if (!Game::ballManager->BallsAreMoving()) {
        mouseangle = Game::ballManager->mouseangle;
        texPos = Game::ballManager->cueBall->position;
    }
    else {
        ballSeparation = 5;
    }

    //bind the texture
    texture->Bind();

    //using a model view projection matrix to display the cue texture but in this case the view does not change
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(texPos.x, texPos.y, 0));
    //multiplying the model with a translate vector that keeps the point of the cue facing the ball
    model = glm::translate(model, glm::vec3(glm::cos(mouseangle)*82, -glm::sin(mouseangle)*82, 0));
    //translating the model so that there is a slight gap between the ball and the cue
    model = glm::translate(model, glm::vec3(glm::sin(mouseangle)*ballSeparation, glm::cos(mouseangle)*ballSeparation, 0));
    //rotating the texture around the ball relative to the mouse angle (the angle between the mouse and the cue ball)
    model = glm::rotate(model, -(mouseangle) + glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(1.0f));
    //the projection is in pixel space, the window size is 1270 to 670
    glm::mat4 projection = glm::ortho(0.0, 1270.0, 670.0, 0.0);
    glm::mat4 mvp = projection * model;
    texture->shader->Bind();
    texture->shader->SetUniformMat4f("u_MVP", mvp);
    Game::renderer->Draw(*(texture->va), *(texture->ib), *(texture->shader));

    
}
