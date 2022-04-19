#pragma once
#include "AssetManager.h"
#include <SDL.h>


class Hole {

public:

    Hole(float posx, float posy, float r);
    void printHole();
    void draw();

    Vector2D position;
    Vector2D texPos;
    Texture * texture;
    float radius;

};