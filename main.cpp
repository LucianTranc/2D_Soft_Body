#include <SDL.h>
#include "Game.h"
#include <iostream>
using namespace std;

Game* game = nullptr;

int main(int argc, char* argv[]) {


    const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("SoftBody", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 780, false);

	//load font library
	if (TTF_Init() == -1)
		std::cout << "Error : SDL_TTF" << std::endl;

	while (game->isRunning) {
		
		frameStart = SDL_GetTicks();

		game->getInputState();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}
	game->clean();
	
	return 0;

}