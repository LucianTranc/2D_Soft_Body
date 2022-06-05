#include "Ball.h"
#include "Game.h"

//Set initialized variables
Ball::Ball(float posx, float posy, float r, float m)
{
    position.x = posx;
    position.y = posy;
    radius = r;
    mass = m;

    circle = new Circle(posx, posy, r);
}

//print ball information to the console
void Ball::printBall()
{
    std::cout<<"Ball"<<std::endl;
    std::cout<<position.x<<std::endl;
    std::cout<<position.y<<std::endl;
    std::cout<<velocity.x<<std::endl;
    std::cout<<velocity.y<<std::endl;
    std::cout<<mass<<std::endl;
}

void Ball::draw() {
    
    circle->draw();
    
}

//handles the physics updates for each ball
void Ball::updatePhysics()
{
    //gravity
    velocity.y = velocity.y + 0.02;

    //air friction
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

    circle->update(position.x, position.y, radius);
    
}