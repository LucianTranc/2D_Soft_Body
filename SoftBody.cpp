#include "SoftBody.h"

SoftBody::SoftBody(float xSpawn, float ySpawn, float spacing, int height, int width)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            balls.push_back(new Ball(xSpawn + (j*spacing), ySpawn + (i * spacing), 13.0, "white"));      
        }
    }

    for (int i = 0; i < balls.size(); i++)
    {
        if ((i + 1) < balls.size() && (i + 1) % width != 0)
        {
            springs.push_back(new Spring(balls[i], balls[i+1]));
        }
        if ((i + width) < balls.size())
        {
            springs.push_back(new Spring(balls[i], balls[i + width]));
        }
        if ((i + width + 1) < balls.size() && (i + 1) % width != 0)
        {
            springs.push_back(new Spring(balls[i], balls[i + width + 1]));
        }
        if ((i - width + 1) < balls.size() && (i - width + 1) >= 0 && (i + 1) % width != 0)
        {
            springs.push_back(new Spring(balls[i], balls[i - width + 1]));
        }
    }

}

