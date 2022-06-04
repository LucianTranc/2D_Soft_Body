#pragma once
#include "AssetManager.h"
#include "Ball.h"
#include "Line.h"
#include <SDL.h>


class Spring {

public:

    Spring(Ball * ball_1, Ball * ball_2);
    void draw();
    void update();
    void updatePhysics();

    float length;
    float restingLength;
    float relativeLength;
    float dampingFactor;

    Ball * ball1;
    Ball * ball2;
    Line * line;
};