#include "Ball.h"
#include "BallManager.h"
#include "Game.h"

//this method was created when the SDL renderer was in use.
//I didn't implement draw calls for lines with OpenGL since I used the gizmos for debugging more than anything.
void BallManager::drawGizmos() {

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
void BallManager::drawBalls() {

    for (auto & b : balls) {
    	b->draw();
	}

}

//draw all the holes
void BallManager::drawHoles() {

    for (auto & h : holes) {
    	h->draw();
	}

}

//draw all the edges
void BallManager::drawEdges() {

    for (auto & e : edges) {
    	e->draw();
	}

}

//draw the cue
void BallManager::drawCue() {

    cue->draw();

}

//create the cue
void BallManager::CreateCue() {
    
    cue = new Cue();

}

//returns true if there are any balls in motion
bool BallManager::BallsAreMoving() {
    
    for (auto& b : balls) {
        if (b->velocity.x != 0 || b->velocity.y != 0) 
            return true;
    }
    return false;

}

//Add a ball to the game
//isCue is used to assign a ball as the cue ball
void BallManager::AddBall(float px, float py, float r, int id, bool isCue, const char * texturePath) {

    if (isCue) {
        cueBall = new Ball(px, py, r, id, texturePath);
        balls.push_back(cueBall);
    }
    else 
        balls.push_back(new Ball(px, py, r, id, texturePath));

}

//add edge to the game
void BallManager::AddEdge(float px1, float py1, float px2, float py2, float r) {

    edges.push_back(new Edge(px1, py1, px2, py2, r));

}

//add hole to the game
void BallManager::AddHole(float px, float py, float r) {

    holes.push_back(new Hole(px, py, r));

} 

//respawn the cue ball
void BallManager::RespawnCue() {

    AddBall(350.0, 335.0, 13.0, 16, true, "white");

}

void BallManager::updatePhysics() {

    //clear the list of collisions
    ballCollisions.clear();
    edgeCollisions.clear();

    //this first loop checks all balls agains all other balls
	for (auto & a : balls) {
    	for (auto & b : balls) {
            //skip when comparing a ball to itself
			if (a->id == b->id)
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
                Ball* fakeBall = new Ball(collisionPoint->x, collisionPoint->y, e->radius, -1);
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

    //check each ball with each hole
    int ballindex = 0;
    for (auto & b : balls) {
    	for (auto & h : holes) {
			//check if the hole and ball collide
			if (Collision::DetectCollisionHole(b, h)) {
                //if the ball hits a hole and it is the cue ball, then a flag is raised
                //The cueball will be respawned the next time all the balls are stationary
                if (b == cueBall) {
                    balls.erase(balls.begin() + ballindex);
                    queueRespawn = true;
                }
                else
                    balls.erase(balls.begin() + ballindex);
                break;
			}
            
		}
        ballindex++;
	} 

    //update the physics of the balls after all the collisions
    for (auto& b : balls) {
        b->updatePhysics();
    }

}

void BallManager::update() {

    //if the respawn cue flag is raised then reset it and respawn the cue ball
    if (queueRespawn && !BallsAreMoving()) {
        queueRespawn = false;
        RespawnCue();
    }

    //get the mouse position and calculate the angle between the mouse and the cueball
    SDL_GetMouseState(&mousex, &mousey);
	mouseangle = std::atan2(mousex - cueBall->position.x, mousey - cueBall->position.y);

    //update all balls
    for (auto& b : balls) {
        b->update();
    }

    //if the player presses the spacebar while the mouse is over a ball then mark it is a the drag ball
    if (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_SPACE) {   
        for (auto& b : balls) {
            if (abs(mousex - b->position.x) < b->radius && abs(mousey - b->position.y) < b->radius) {
                selectedDragBall = b;
                break;
            }
        }
    }

    //if the player releases the spacebar then deselect the ball
    if (Game::event.type == SDL_KEYUP && Game::event.key.keysym.sym == SDLK_SPACE) {
        selectedDragBall = nullptr; 
    }

    //if the mousebutton is pressed while no balls are moving then mark the cueball as the ball to hit
    if ((Game::event.type == SDL_MOUSEBUTTONDOWN && selectedHitBall == nullptr) && !BallsAreMoving()) {
        mousedown = true;
        selectedHitBall = cueBall;
    }
    else if (mousedown && selectedHitBall) {
        //if the mouse is being held down then add to the power of the hit and drag the cue backwards
        hitPower += 4;
        cue->ballSeparation = hitPower/2 + 5;

    }
    //if the mousebutton is released then reset the cue, add the the balls velocity and reset variables
    if (Game::event.type == SDL_MOUSEBUTTONUP) {
        cue->ballSeparation = 5;
        if (selectedHitBall) {
            selectedHitBall->velocity.x = -glm::sin(mouseangle) * hitPower / 50;
            selectedHitBall->velocity.y = -glm::cos(mouseangle) * hitPower / 50;
            hitPower = 0;
        }
        selectedHitBall = nullptr;
        mousedown = false;
    }

    //if there is a drag ball selected then move it
    if (selectedDragBall) {
        selectedDragBall->position.x = mousex;
        selectedDragBall->position.y = mousey;
    }
    
}