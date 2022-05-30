#include "Ball.h"
#include "ObjectManager.h"
#include "Game.h"

//this method was created when the SDL renderer was in use.
//I didn't implement draw calls for lines with OpenGL since I used the gizmos for debugging more than anything.
void ObjectManager::drawGizmos() {

    /* SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
	for (auto& c : ballCollisions) {
        SDL_RenderDrawLine(Game::renderer, c.first->position.x, c.first->position.y, c.second->position.x, c.second->position.y);
	}
    if (selectedHitBall) {
        SDL_RenderDrawLine(Game::renderer, selectedHitBall->position.x, selectedHitBall->position.y, mousex, mousey);
    }
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255); */

}

//draw all the balls
void ObjectManager::drawBalls()
{
    for (auto & b : balls) {
    	b->draw();
	}
}

void ObjectManager::drawSprings()
{
    for (auto & s : springs) {
    	s->draw();
	}
}

void ObjectManager::drawLines()
{
    for (auto & l : lines) {
    	l->draw();
	}
}

//draw all the edges
void ObjectManager::drawEdges() {

    for (auto & e : edges) {
    	e->draw();
	}

}

//returns true if there are any balls in motion
bool ObjectManager::BallsAreMoving() {
    
    for (auto& b : balls) {
        if (b->velocity.x != 0 || b->velocity.y != 0) 
            return true;
    }
    return false;

}

//Add a ball to the game
//isCue is used to assign a ball as the cue ball
void ObjectManager::AddBall(float px, float py, float r, const char * texturePath) {

    balls.push_back(new Ball(px, py, r, texturePath));
}

//add edge to the game
void ObjectManager::AddEdge(float px1, float py1, float px2, float py2, float r) {

    edges.push_back(new Edge(px1, py1, px2, py2, r));

}

//add spring to the game
void ObjectManager::AddSpring(Ball * ball_1, Ball * ball_2) {

    springs.push_back(new Spring(ball_1, ball_2));

}

void ObjectManager::AddLine(float px1, float py1, float px2, float py2) {

    lines.push_back(new Line(px1, py1, px2, py2));

}

void ObjectManager::AddSoftBody(int px, int py, float h, float w)
{
    SoftBody * sb = new SoftBody(px, py, h, w);
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

void ObjectManager::updatePhysics() {

    //clear the list of collisions
    ballCollisions.clear();
    edgeCollisions.clear();

    //this first loop checks all balls agains all other balls
	for (auto & a : balls) {
    	for (auto & b : balls) {

            //skip when comparing a ball to itself
			if (a == b)
				continue;

			//check if balls collide
			if (Collision::DetectCollision(a, b)) {
                
				bool duplicate = false;
                //create the opposite pairing of balls and check if the opposite pairing is already
                //in the list of collisions
				std::pair<Ball*, Ball*> tempPair;
				tempPair = {b,a};
				for (auto& c : ballCollisions) {
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
    for (auto& c : ballCollisions) {
        Collision::DynamicCollision(c.first, c.second);
	}

    //check all balls against all edges
    for (auto & b : balls) {
    	for (auto & e : edges) {
			//DetectCollisionEdge returns the closest point on the edge if there is a collision
            Vector2D* collisionPoint = Collision::DetectCollisionEdge(b, e);
            //if collisionPoint isn't a nullptr then that means collision was detected
			if (collisionPoint) {
                //create a fake temporary ball at the point of collision and store the original ball and the fake ball in a pair
                Ball* fakeBall = new Ball(collisionPoint->x, collisionPoint->y, e->radius);
                fakeBall->velocity.x = -b->velocity.x;
                fakeBall->velocity.y = -b->velocity.y;
				edgeCollisions.push_back({b,fakeBall});
			}
		}
	} 

    //handle the ball to edge collisions
    for (auto& c : edgeCollisions) {
        Collision::DynamicCollision(c.first, c.second);
	}

    for (auto& s : springs) {
        s->updatePhysics();
    }

    //update the physics of the balls after all the collisions
    for (auto& b : balls) {
        b->updatePhysics();
    }



}

void ObjectManager::update() {

    //update all balls
    for (auto& b : balls) {
        b->update();
    }

    for (auto& s : springs) {
        s->update();
    }

    //if the player presses the spacebar while the mouse is over a ball then mark it is a the drag ball
    if (Game::keystates[SDL_SCANCODE_SPACE] && selectedDragBall == nullptr) {   
        for (auto& b : balls) {
            if (abs(Game::mousex - b->position.x) < b->radius && abs(Game::mousey - b->position.y) < b->radius) {
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
    

    //if the player releases the spacebar then deselect the ball
    /* if (Game::event.type == SDL_KEYUP && Game::event.key.keysym.sym == SDLK_SPACE) {
        selectedDragBall = nullptr; 
    } */

    //if there is a drag ball selected then move it
    if (selectedDragBall) {
        dragBallVelocity.x = (Game::mousex - selectedDragBall->position.x);
        dragBallVelocity.y = (Game::mousey - selectedDragBall->position.y);
        selectedDragBall->position.x = Game::mousex;
        selectedDragBall->position.y = Game::mousey;
    }
    
}