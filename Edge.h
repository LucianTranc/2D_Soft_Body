#pragma once
#include "AssetManager.h"
#include <SDL.h>
#include "Line.h"
#include "Circle.h"

//Edges are composed of two positions on the board forming a line segment.
//The edges collide with balls at a given radius distance resulting in a pill shaped collider
class Edge {

public:

    Edge(float pos1x, float pos1y, float pos2x, float pos2y, float r);

    void printID();
    void draw();

    Vector2D position1;
    Vector2D position2;
    Line * line1;
    Line * line2;
    Circle * circle1;
    Circle * circle2;
    float radius;

};