#include "Spring.h"
#include "Game.h"

//initialize variables
Spring::Spring(Ball * ball_1, Ball * ball_2, float damping, float springForce)
{
    ball1 = ball_1;
    ball2 = ball_2;
    line = new Line(ball1->position.x, ball1->position.y, ball2->position.x, ball2->position.y);
    restingLength = sqrt(pow(ball2->position.x - ball1->position.x, 2) + pow(ball2->position.y - ball1->position.y, 2) * 1.0);
    dampingFactor = damping;
    springForceFactor = springForce;
}

void Spring::updatePhysics()
{
    length = sqrt(pow(ball2->position.x - ball1->position.x, 2) + pow(ball2->position.y - ball1->position.y, 2) * 1.0);

    relativeLength = length - restingLength;

    vec2 directionA = {ball2->position.x - ball1->position.x, ball2->position.y - ball1->position.y};
    vec2 directionB = {ball1->position.x - ball2->position.x, ball1->position.y - ball2->position.y};
    vec2 normalizedDirectionA = directionA/length;
    vec2 normalizedDirectionB = directionB/length;
    vec2 velocityDifference = {ball2->velocity.x - ball1->velocity.x, ball2->velocity.y - ball1->velocity.y};
    float dotProduct = dot(normalizedDirectionA, velocityDifference);

    vec2 dampingForceA = normalizedDirectionA * dotProduct;
    vec2 dampingForceB = normalizedDirectionB * dotProduct;

    vec2 springForceA = normalizedDirectionA * relativeLength;
    vec2 springForceB = normalizedDirectionB * relativeLength;

    springForceA = springForceA/springForceFactor;
    springForceB = springForceB/springForceFactor;

    ball1->velocity.x = ball1->velocity.x + springForceA.x;
    ball1->velocity.y = ball1->velocity.y + springForceA.y;
    ball2->velocity.x = ball2->velocity.x + springForceB.x;
    ball2->velocity.y = ball2->velocity.y + springForceB.y;

    dampingForceA = dampingForceA/dampingFactor;
    dampingForceB = dampingForceB/dampingFactor;

    ball1->velocity.x = ball1->velocity.x + dampingForceA.x;
    ball1->velocity.y = ball1->velocity.y + dampingForceA.y;
    ball2->velocity.x = ball2->velocity.x + dampingForceB.x;
    ball2->velocity.y = ball2->velocity.y + dampingForceB.y;
}

void Spring::update()
{
    vec3 color = {relativeLength/5, 0, -relativeLength/5};
    line->update(ball1->position.x, ball1->position.y, ball2->position.x, ball2->position.y, color);
}

void Spring::draw()
{
    line->draw();
}
