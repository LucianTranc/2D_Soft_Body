#pragma once
//#include "AssetManager.h"
#include "Ball.h"
#include "Edge.h"
#include "Spring.h"
#include "Line.h"
#include "Circle.h"
#include "SoftBody.h"
#include <SDL.h>
#include <vector>

class Ball;
class Hole;
class Edge;

class ObjectManager {

public:

    void AddBall(float px, float py, float r, float m);
    void AddEdge(float px1, float py1, float px2, float py2, float r);
    void AddSpring(Ball * ball_1, Ball * ball_2, float damping, float spring);
    void AddLine(float px1, float py1, float px2, float py2);
    void AddCircle(float px, float py, float r);
    void AddSoftBody(int px, int py, float s, float h, float w, float r, float m, float damping, float spring);
    void drawGizmos();
    void drawBalls();
    void drawEdges();
    void drawSprings();
    void drawLines();
    void drawCircles();
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
    std::vector<Circle*> circles;
    std::vector<SoftBody*> softBodies;

    //list of collisions
	std::vector<std::pair<Ball*,Ball*>> ballCollisions;
	std::vector<std::pair<Ball*,Ball*>> edgeCollisions;
    
};