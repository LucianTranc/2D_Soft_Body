#include "Edge.h"
#include "AssetManager.h"
#include "Game.h"

//initialize variables
Edge::Edge(float pos1x, float pos1y, float pos2x, float pos2y, float r)
{
    position1.x = pos1x;
    position1.y = pos1y;
    position2.x = pos2x;
    position2.y = pos2y;
    radius = r;

    float nx = -(position1.y - position2.y);
	float ny = (position1.x - position2.x);
	float d = sqrt(nx*nx + ny * ny);
	nx /= d;
	ny /= d;

    line1 = new Line(position1.x + nx * radius, position1.y + ny * radius, position2.x + nx * radius, position2.y + ny * radius);
    line2 = new Line(position1.x - nx * radius, position1.y - ny * radius, position2.x - nx * radius, position2.y - ny * radius);
    circle1 = new Circle(position1.x, position1.y, radius);
    circle2 = new Circle(position2.x, position2.y, radius);
}


void Edge::draw()
{
    circle1->draw();
    circle2->draw();
    line1->draw();
    line2->draw();
}