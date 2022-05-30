#include "SoftBody.h"

SoftBody::SoftBody(int xSpawn, int ySpawn, int height, int width)
{
    balls.push_back(new Ball(1030.0f, 180.0, 13.0, "white")); //0,0
    balls.push_back(new Ball(1030.0f + 30.0, 180.0, 13.0, "white")); //1,0
    balls.push_back(new Ball(1030.0f, 180.0 + 30.0, 13.0, "white")); //0,1
    balls.push_back(new Ball(1030.0f + 30.0, 180.0 + 30.0, 13.0, "white")); //1,1
    balls.push_back(new Ball(1030.0f + 60.0, 180.0, 13.0, "white")); //2,0
    balls.push_back(new Ball(1030.0f + 60.0, 180.0 + 30.0, 13.0, "white")); //2,1
    balls.push_back(new Ball(1030.0f + 60.0, 180.0 + 60.0, 13.0, "white")); //2,2
    balls.push_back(new Ball(1030.0f + 30.0, 180.0 + 60.0, 13.0, "white")); //1,2
    balls.push_back(new Ball(1030.0f, 180.0 + 60.0, 13.0, "white")); //0,2

    springs.push_back(new Spring(balls[0], balls[1]));
    springs.push_back(new Spring(balls[0], balls[2]));
    springs.push_back(new Spring(balls[0], balls[3]));
    springs.push_back(new Spring(balls[3], balls[2]));
    springs.push_back(new Spring(balls[3], balls[1]));
    springs.push_back(new Spring(balls[2], balls[1]));
    springs.push_back(new Spring(balls[4], balls[1]));
    springs.push_back(new Spring(balls[3], balls[5]));
    springs.push_back(new Spring(balls[6], balls[7]));
    springs.push_back(new Spring(balls[3], balls[7]));
    springs.push_back(new Spring(balls[2], balls[8]));
    springs.push_back(new Spring(balls[4], balls[5]));
    springs.push_back(new Spring(balls[5], balls[6]));
    springs.push_back(new Spring(balls[8], balls[7]));
    springs.push_back(new Spring(balls[2], balls[7]));
    springs.push_back(new Spring(balls[8], balls[3]));
    springs.push_back(new Spring(balls[3], balls[6]));
    springs.push_back(new Spring(balls[5], balls[7]));
    springs.push_back(new Spring(balls[3], balls[4]));
    springs.push_back(new Spring(balls[1], balls[5]));

}

