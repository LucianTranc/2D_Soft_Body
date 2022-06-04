#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"

class Collider;

class Ball {

public:

    Ball(float posx, float posy, float r, const char * texturePath = nullptr);

    void printBall();
    void draw();
    void update();
    void updatePhysics();
    void resetCue();

    Vector2D position;
    Vector2D texPos;
    Vector2D velocity;
    Texture * texture;
    float radius;
    float mass = 10;

};