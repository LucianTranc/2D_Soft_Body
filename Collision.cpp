#include "Collision.h"

//method that handles elastic collisions between two balls
void Collision::DynamicCollision(Ball * b1, Ball * b2) 
{
    //https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Balls1.cpp
    //https://en.wikipedia.org/wiki/Elastic_collision
    float distance = sqrtf((b1->position.x - b2->position.x)*(b1->position.x - b2->position.x) + (b1->position.y - b2->position.y)*(b1->position.y - b2->position.y));
    float nx = (b2->position.x - b1->position.x) / distance;
    float ny = (b2->position.y - b1->position.y) / distance;
    float kx = (b1->velocity.x - b2->velocity.x);
    float ky = (b1->velocity.y - b2->velocity.y);
    float p = 2.0 * (nx * kx + ny * ky) / (b1->mass + b2->mass);
    b1->velocity.x = b1->velocity.x - p * b2->mass * nx;
    b1->velocity.y = b1->velocity.y - p * b2->mass * ny;
    b2->velocity.x = b2->velocity.x + p * b1->mass * nx;
    b2->velocity.y = b2->velocity.y + p * b1->mass * ny;

};

bool Collision::DetectCollision(Ball * b1, Ball * b2) {

    //find distance between the centers of the two balls
    float distancex = b1->position.x - b2->position.x;
    float distancey = b1->position.y - b2->position.y;
    float distance = sqrt(pow(distancex, 2) + pow(distancey, 2));
    //calculate the overlap by subtracting the radius of both balls from the distance between them
    float overlap = 0.5f * (-(distance - b1->radius - b2->radius));

    //if the distance between the two balls is less than the sum of the radius of both balls then they are colliding
    if (abs(distance) < b1->radius + b2->radius)
    {
        //SDL_RenderDrawLine(Game::renderer, b1->position.x, b1->position.y, b2->position.x, b2->position.y);
        //apply half of the overlap to both balls.
        b1->position.x += overlap * (distancex) / distance;
        b1->position.y += overlap * (distancey) / distance;

        b2->position.x -= overlap * (distancex) / distance;
        b2->position.y -= overlap * (distancey) / distance;
        return true;
    }
    else 
        return false;

};

bool Collision::DetectCollisionHole(Ball * b, Hole * h) {
    
    //calculate the distance between the ball and the hole and if that distance is less than
    //the sum of the radius of the ball and hole then they are colliding.
    float distancex = b->position.x - h->position.x;
    float distancey = b->position.y - h->position.y;
    float distance = sqrt(pow(distancex, 2) + pow(distancey, 2));

    if (abs(distance) < b->radius + h->radius)
        return true;
    else 
        return false;

};

Vector2D* Collision::DetectCollisionEdge(Ball * b, Edge * e) {

    //this function detects collisions between an edge and a ball.
    //this is done by finding the closest distance between a point and a line segment.
    //the line segment being the line formed by the two position attributes of the edge.
    //and the point being the position of the ball.


    //the three points in questions are separated into 2d vectors for simplicity.
    //A and B are the points forming the line segment and C is the point from which we need to calculate the distance.
    Vector2D A;
    A.x = e->position1.x;
    A.y = e->position1.y;
    Vector2D B;
    B.x = e->position2.x;
    B.y = e->position2.y;
    Vector2D C;
    C.x = b->position.x;
    C.y = b->position.y;

    //the distance is found using the equation t = [(C-A)*(B-C)]/[B-A]^2
    //where the * is the dot product between the resulting two vectors v1 and v2 below.
    //[B-A]^2 is the lenght of the line segment squared.
    
    Vector2D v1;
    v1.x = C.x - A.x;
    v1.y = C.y - A.y;
    Vector2D v2;
    v2.x = B.x - A.x;
    v2.y = B.y - A.y;

    float distanceSq = ((B.x - A.x)*(B.x - A.x) + (B.y - A.y)*(B.y - A.y));
    float t = (v1.x * v2.x + v1.y * v2.y)/distanceSq;

    //this equation yeilds a t value that can tell us where the point is in relation to the line segment.
    //if the t value is between 0 and 1 then the closest point on the segment lies somewhere between points A and B
    //if the t value is less then 0 then the closest point is B
    //if the t value is more than 1 then the closest point is A

    //once we determine which of the three outcomes we are dealing with we can find the vector coordinates to send as a return value
    if (0 < t && t <=1) {
        //this formula yeilds the distance of the normal from the line segment to the point
        float denominator = sqrt((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y));
        float normal = abs((B.x-A.x)*(A.y-C.y) - (A.x-C.x)*(B.y-A.y))/denominator;
        //if the normal is less than the sum of the radius then we have a collision
        if (normal < b->radius + e->radius) {
            Vector2D closePoint;
            closePoint.x = A.x + t*(B.x - A.x);
            closePoint.y = A.y + t*(B.y - A.y);
            float overlap = (-(normal - b->radius - e->radius));
            float distancex = b->position.x - closePoint.x;
            float distancey = b->position.y - closePoint.y;
            b->position.x += 1.0f * overlap * (distancex) / normal;
            b->position.y += 1.0f * overlap * (distancey) / normal;
            return new Vector2D(closePoint.x, closePoint.y);
        }
    }
    else if (t < 0) {
        //when we are dealing with one end of the line we can handle it similarlly to the way we detect
        //collision between two balls.
        float distance1x = e->position1.x - b->position.x;
        float distance1y = e->position1.y - b->position.y;
        float distance1 = sqrt(pow(distance1x, 2) + pow(distance1y, 2));
        if (distance1 < b->radius + e->radius) {
            float distancex = b->position.x - e->position1.x;
            float distancey = b->position.y - e->position1.y;
            float distance = sqrt(pow(distancex, 2) + pow(distancey, 2));
            float overlap = (-(distance - b->radius - e->radius));
            b->position.x += 1.0f * overlap * (distancex) / distance;
            b->position.y += 1.0f * overlap * (distancey) / distance;
            return new Vector2D(e->position1.x, e->position1.y);
        }

    }
    else {

        float distance2x = e->position2.x - b->position.x;
        float distance2y = e->position2.y - b->position.y;
        float distance2 = sqrt(pow(distance2x, 2) + pow(distance2y, 2));
        if (distance2 < b->radius + e->radius) {
            float distancex = b->position.x - e->position2.x;
            float distancey = b->position.y - e->position2.y;
            float distance = sqrt(pow(distancex, 2) + pow(distancey, 2));
            float overlap = (-(distance - b->radius - e->radius));
            b->position.x += 1.0f * overlap * (distancex) / distance;
            b->position.y += 1.0f * overlap * (distancey) / distance;
            return new Vector2D(e->position2.x, e->position2.y);
        }

    }


    return nullptr;

};