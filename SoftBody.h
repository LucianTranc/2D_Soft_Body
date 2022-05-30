#pragma once
#include "AssetManager.h"
#include "Ball.h"
#include "Spring.h"
#include <SDL.h>

class SoftBody {

public:

    SoftBody(int xSpawn, int ySpawn, int height, int width);

    std::vector<Ball*> balls;
    std::vector<Spring*> springs;

};