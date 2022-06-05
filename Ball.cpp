#include "Ball.h"
#include "Game.h"

//Set initialized variables
Ball::Ball(float posx, float posy, float r,  const char * texturePath) {

    position.x = posx;
    position.y = posy;
    radius = r;

    circle = new Circle(posx, posy, r);

    //texPos.x = position.x - radius;
	//texPos.y = position.y - radius;

    //if (texturePath)
    //    texture = Game::assetManager->GetTexture(texturePath);

}

//print ball information to the console
void Ball::printBall() {
    std::cout<<"Ball"<<std::endl;
    std::cout<<position.x<<std::endl;
    std::cout<<position.y<<std::endl;
    std::cout<<velocity.x<<std::endl;
    std::cout<<velocity.y<<std::endl;
    std::cout<<mass<<std::endl;
}

//resets a ball to the default cue location. This method is called only 
//when the player sinks the cue ball
void Ball::resetCue() {

    position.x = 350.f;
    position.y = 335.f;

    velocity.x = 0.f;
    velocity.y = 0.f;

}

void Ball::draw() {

    //only draw the ball if it is initialized with a texture
    
    circle->draw();
    
}

//handles the physics updates for each ball
void Ball::updatePhysics() {
    
    //gravity
    velocity.y = velocity.y + 0.05;

    //friction
    velocity.x = velocity.x * 0.997;
    velocity.y = velocity.y * 0.997;

    //clamp the velocity to zero to avoid the ball moving very slowly for a long time
    if (abs(velocity.x*velocity.x + velocity.y*velocity.y) < 0.0001)
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    //update the position with the velocity
    position.x += velocity.x;
    position.y += velocity.y;
    
}

//handles non physics updates
void Ball::update() {

    //teleport the ball to the opposite side of the screen if it somehow gets past the edges
    if (position.x < 0)
        position.x = Game::screenSize->x;
    
    if (position.x > Game::screenSize->x)
        position.x = 0;

    if (position.y < 0)
        position.y = Game::screenSize->y;
    
    if (position.y > Game::screenSize->y)
        position.y = 0;

    //update the texture position with the new position set in updatePhysics()
    circle->update(position.x, position.y, radius);
    //texPos.x = position.x - radius;
    //texPos.y = position.y - radius;
    
}