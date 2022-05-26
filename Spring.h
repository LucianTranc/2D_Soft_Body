#pragma once
#include "AssetManager.h"
#include <SDL.h>


class Spring {

public:

    Spring(float pos1x, float pos1y, float pos2x, float pos2y);
    void printSpring();
    void draw();

    Vector2D position1;
    Vector2D position2;
    Shader * shader;
    VertexArray * va;
    VertexBuffer * vb;
    VertexBufferLayout * layout;
};