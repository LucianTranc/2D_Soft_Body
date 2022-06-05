#include "Ball.h"
#include "ObjectManager.h"
#include "Game.h"

void ObjectManager::drawBalls()
{
    for (auto & b : balls)
    {
    	b->draw();
	}
}

void ObjectManager::drawSprings()
{
    for (auto & s : springs)
    {
    	s->draw();
	}
}

void ObjectManager::drawLines()
{
    for (auto & l : lines)
    {
    	l->draw();
	}
}

void ObjectManager::drawCircles()
{
    for (auto & c : circles)
    {
    	c->draw();
	}
}

void ObjectManager::drawEdges()
{
    for (auto & e : edges)
    {
    	e->draw();
	}
}

//returns true if there are any balls in motion
bool ObjectManager::BallsAreMoving()
{
    for (auto& b : balls)
    {
        if (b->velocity.x != 0 || b->velocity.y != 0) 
            return true;
    }
    return false;
}

void ObjectManager::AddBall(float px, float py, float r, float m)
{
    balls.push_back(new Ball(px, py, r, m));
}

void ObjectManager::AddEdge(float px1, float py1, float px2, float py2, float r)
{
    edges.push_back(new Edge(px1, py1, px2, py2, r));
}

void ObjectManager::AddSpring(Ball * ball_1, Ball * ball_2, float damping, float spring)
{
    springs.push_back(new Spring(ball_1, ball_2, damping, spring));
}

void ObjectManager::AddLine(float px1, float py1, float px2, float py2)
{
    lines.push_back(new Line(px1, py1, px2, py2));
}

void ObjectManager::AddCircle(float px, float py, float r)
{
    circles.push_back(new Circle(px, py, r));
}

void ObjectManager::AddSoftBody(int px, int py, float s, float h, float w, float r, float m, float damping, float spring)
{
    SoftBody * sb = new SoftBody(px, py, s, h, w, r, m, damping, spring);
    softBodies.push_back(sb);
    for (auto &b : sb->balls)
    {
        balls.push_back(b);
    }
    for (auto &s : sb->springs)
    {
        springs.push_back(s);
    }
}

void ObjectManager::updatePhysics()
{
    //clear the list of collisions
    ballCollisions.clear();
    edgeCollisions.clear();

    //this first loop checks all balls agains all other balls
	for (auto & a : balls)
    {
    	for (auto & b : balls)
        {
            //skip when comparing a ball to itself
			if (a == b)
				continue;

			//check if balls collide
			if (Collision::DetectCollision(a, b))
            {
				bool duplicate = false;
                //create the opposite pairing of balls and check if the opposite pairing is already
                //in the list of collisions
				std::pair<Ball*, Ball*> tempPair;
				tempPair = {b,a};
				for (auto& c : ballCollisions)
                {
					if (c == tempPair)
						duplicate = true;
				}
                //if the pair isn't a duplicate add it to the ball collision list
				if (!duplicate)
					ballCollisions.push_back({a,b});
			}
		}
	}

    // go through the ball collision list and handle the elastic collision physics
    for (auto& c : ballCollisions)
    {
        Collision::DynamicCollision(c.first, c.second);
	}

    //check all balls against all edges
    for (auto & b : balls)
    {
    	for (auto & e : edges)
        {
			//DetectCollisionEdge returns the closest point on the edge if there is a collision
            Vector2D* collisionPoint = Collision::DetectCollisionEdge(b, e);
            //if collisionPoint isn't a nullptr then that means collision was detected
			if (collisionPoint)
            {
                //create a fake temporary ball at the point of collision and store the original ball and the fake ball in a pair
                Ball* fakeBall = new Ball(collisionPoint->x, collisionPoint->y, e->radius, b->mass);
                fakeBall->velocity.x = -b->velocity.x;
                fakeBall->velocity.y = -b->velocity.y;
				edgeCollisions.push_back({b,fakeBall});
			}
		}
	} 

    //handle the ball to edge collisions
    for (auto& c : edgeCollisions)
    {
        Collision::DynamicCollision(c.first, c.second);
	}

    for (auto& s : springs)
    {
        s->updatePhysics();
    }

    //update the physics of the balls after all the collisions
    for (auto& b : balls)
    {
        b->updatePhysics();
    }
}

void ObjectManager::update()
{
    for (auto& b : balls)
    {
        b->update();
    }

    for (auto& s : springs)
    {
        s->update();
    }

    //if the player presses the spacebar while the mouse is over a ball then mark it is a the drag ball
    if (Game::keystates[SDL_SCANCODE_SPACE] && selectedDragBall == nullptr)
    {   
        for (auto& b : balls)
        {
            if (abs(Game::mousex - b->position.x) < b->radius && abs(Game::mousey - b->position.y) < b->radius)
            {
                selectedDragBall = b;
                selectedDragBall->velocity.x = 0;
                selectedDragBall->velocity.y = 0;
                break;
            }
        }
    }

    if (!Game::keystates[SDL_SCANCODE_SPACE])
    {
        if (selectedDragBall)
        {
            selectedDragBall->velocity.x = dragBallVelocity.x;
            selectedDragBall->velocity.y = dragBallVelocity.y;
        }
        selectedDragBall = nullptr; 
    }
    
    //if there is a drag ball selected then move it
    if (selectedDragBall)
    {
        selectedDragBall->velocity.x = 0;
        selectedDragBall->velocity.y = 0;
        dragBallVelocity.x = (Game::mousex - selectedDragBall->position.x);
        dragBallVelocity.y = (Game::mousey - selectedDragBall->position.y);
        selectedDragBall->position.x = Game::mousex;
        selectedDragBall->position.y = Game::mousey;
    }
}