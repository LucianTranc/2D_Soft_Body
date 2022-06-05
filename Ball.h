#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "Circle.h"

class Collider;

class Ball {

public:

    Ball(float posx, float posy, float r, float m);

    void printBall();
    void draw();
    void update();
    void updatePhysics();

    Circle * circle;

    Vector2D position;
    Vector2D velocity;
    float radius;
    float mass = 10;

};