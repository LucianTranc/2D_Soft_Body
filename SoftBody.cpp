#include "SoftBody.h"

SoftBody::SoftBody(float xSpawn, float ySpawn, float spacing, int height, int width, float r, float m, float damping, float spring)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            balls.push_back(new Ball(xSpawn + (j*spacing), ySpawn + (i * spacing), r, m));      
        }
    }

    for (int i = 0; i < balls.size(); i++)
    {
        if ((i + 1) < balls.size() && (i + 1) % width != 0)
        {
            springs.push_back(new Spring(balls[i], balls[i+1], damping, spring));
        }
        if ((i + width) < balls.size())
        {
            springs.push_back(new Spring(balls[i], balls[i + width], damping, spring));
        }
        if ((i + width + 1) < balls.size() && (i + 1) % width != 0)
        {
            springs.push_back(new Spring(balls[i], balls[i + width + 1], damping, spring));
        }
        if ((i - width + 1) < balls.size() && (i - width + 1) >= 0 && (i + 1) % width != 0)
        {
            springs.push_back(new Spring(balls[i], balls[i - width + 1], damping, spring));
        }
    }
}

