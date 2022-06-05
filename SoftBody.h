#pragma once
#include "AssetManager.h"
#include "Ball.h"
#include "Spring.h"
#include <SDL.h>

class SoftBody {

public:

    SoftBody(float xSpawn, float ySpawn, float spacing, int height, int width, float radius, float m, float damping, float spring);

    std::vector<Ball*> balls;
    std::vector<Spring*> springs;

};