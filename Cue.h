#pragma once
//#include "AssetManager.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"

class Collider;

class Cue {

public:

    Cue();

    void draw();

    Vector2D position;
    Vector2D texPos;
    Texture * texture;
    float rotation;
    float ballSeparation = 5.f;
    float mouseangle;

    
};