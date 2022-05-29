#pragma once
//#include "AssetManager.h"
#include "Ball.h"
#include "Edge.h"
#include "Spring.h"
#include "Line.h"
#include <SDL.h>
#include <vector>

class Ball;
class Hole;
class Edge;

class BallManager {

public:

    void AddBall(float px, float py, float r, int id, const char * texturePath);
    void AddEdge(float px1, float py1, float px2, float py2, float r);
    void AddSpring(Ball * ball_1, Ball * ball_2);
    void AddLine(float px1, float py1, float px2, float py2);
    void drawGizmos();
    void drawBalls();
    void drawEdges();
    void drawSprings();
    void drawLines();
    void updatePhysics();
    void update();
    bool BallsAreMoving();

    //the drag ball is the ball marked as the ball to be dragged on screen
    Ball* selectedDragBall;
    Vector2D dragBallVelocity;

    //list of game objects
    std::vector<Ball*> balls;
    std::vector<Edge*> edges;
    std::vector<Spring*> springs;
    std::vector<Line*> lines;

    //list of collisions
	std::vector<std::pair<Ball*,Ball*>> ballCollisions;
	std::vector<std::pair<Ball*,Ball*>> edgeCollisions;
    
};