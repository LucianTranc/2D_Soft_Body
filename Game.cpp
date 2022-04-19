#include "Game.h"
#include "Vector2D.h"
#include <sstream>
#include <cmath>
#include <OpenGL/gl3.h>
#include "Renderer.h"

//initialize static variables
SDL_Event Game::event;
AssetManager* Game::assetManager = new AssetManager();
TextureManager* Game::textureManager = new TextureManager();
BallManager* Game::ballManager = new BallManager();
bool Game::isRunning = false;
Vector2D* Game::screenSize = new Vector2D();
Renderer* Game::renderer = new Renderer();
Table* Game::table = new Table();

Game::Game() {

}
Game::~Game() {
    
}

//initialize the game
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	//initialize sdl video subsystem
	SDL_Init(SDL_INIT_VIDEO);
    std::cout << "Subsystems initialized\n";

	//set SDL OpenGl Attributes
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//create a window
    window = SDL_CreateWindow(
        title,
        xpos,
        ypos,
        width,
        height,
        SDL_WINDOW_OPENGL);
    if (window)
        std::cout << "Window Created\n";

	//create an OpengGL context in the new window
    SDL_GL_CreateContext(window);

	isRunning = true;

	//load font library
	if (TTF_Init() == -1)
		std::cout << "Error : SDL_TTF" << std::endl;

    //projection = glm::ortho(0.0, static_cast<double>(width), static_cast<double>(height), 0.0);

	screenSize->x = width;
	screenSize->y = height;

	//set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//load all game assets (textures and fonts)
	loadAssets();
    
	//initialize the table
	table->init();

	//create all the balls, edges and holes
    createBalls();
	
}


void Game::loadAssets() {

	//load all the textures
    assetManager->AddTexture("ball1", "assets/blackcircle1.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("ball2", "assets/blackcircle1.png", 50.0f, 50.0f, 1270, 670);
    assetManager->AddTexture("ball3", "assets/blackcircle1.png", 30.0f, 30.0f, 1270, 670);
    assetManager->AddTexture("black", "assets/bb_black.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("blue", "assets/bb_blue.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("brown", "assets/bb_brown.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("green", "assets/bb_green.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("orange", "assets/bb_orange.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("purple", "assets/bb_purple.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("red", "assets/bb_red.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("white", "assets/bb_white.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("yellow", "assets/bb_yellow.png", 26.0f, 26.0f, 1270, 670);
    assetManager->AddTexture("table", "assets/PoolTable.png", 1270.0f, 670.0f, 1270, 670);
    assetManager->AddTexture("cue", "assets/cue.png", 420.0f, 170.0f, 1270, 670);

	//enable OpenGl blending and set a blending function
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

}

void Game::createBalls() {

	//add all the balls to the ballManager
	ballManager->AddBall(935.0, 335.0, 13.0, 1, false, "yellow");

	ballManager->AddBall(935.0 + 24.0*1.0, 335.0 + 14.0*1.0, 13.0, 2, false, "red");
	ballManager->AddBall(935.0 + 24.0*1.0, 335.0 - 14.0*1.0, 13.0, 3, false, "blue");

	ballManager->AddBall(935.0 + 24.0*2.0, 335.0 - 14.0*2.0, 13.0, 4, false, "green");
	ballManager->AddBall(935.0 + 24.0*2.0, 335.0 - 14.0*0.0, 13.0, 5, false, "black");
	ballManager->AddBall(935.0 + 24.0*2.0, 335.0 + 14.0*2.0, 13.0, 6, false, "purple");

	ballManager->AddBall(935.0 + 24.0*3.0, 335.0 - 14.0*3.0, 13.0, 7, false, "blue");
	ballManager->AddBall(935.0 + 24.0*3.0, 335.0 - 14.0*1.0, 13.0, 8, false, "yellow");
	ballManager->AddBall(935.0 + 24.0*3.0, 335.0 + 14.0*1.0, 13.0, 9, false, "orange");
	ballManager->AddBall(935.0 + 24.0*3.0, 335.0 + 14.0*3.0, 13.0, 10, false, "brown");

	ballManager->AddBall(935.0 + 24.0*4.0, 335.0 - 14.0*4.0, 13.0, 11, false, "brown");
	ballManager->AddBall(935.0 + 24.0*4.0, 335.0 - 14.0*2.0, 13.0, 12, false, "green");
	ballManager->AddBall(935.0 + 24.0*4.0, 335.0 + 14.0*0.0, 13.0, 13, false, "orange");
	ballManager->AddBall(935.0 + 24.0*4.0, 335.0 + 14.0*2.0, 13.0, 14, false, "purple");
	ballManager->AddBall(935.0 + 24.0*4.0, 335.0 + 14.0*4.0, 13.0, 15, false, "red");

	//cue ball
	ballManager->AddBall(350.0, 335.0, 13.0, 16, true, "white");

	//add edges to the ball manager
	ballManager->AddEdge(112.0, 42.0, 593.0, 42.0, 25.0);
	ballManager->AddEdge(678.0, 42.0, 1155.0, 42.0, 25.0);
	ballManager->AddEdge(1222.0, 110.0, 1222.0, 560.0, 25.0);
	ballManager->AddEdge(678.0, 625.0, 1155.0, 625.0, 25.0);
	ballManager->AddEdge(112.0, 625.0, 593.0, 625.0, 25.0);
	ballManager->AddEdge(45.0, 110.0, 45.0, 560.0, 25.0);

	//add the holes to the ball manager
	ballManager->AddHole(635.0, 42.0, 15);
	ballManager->AddHole(59.0, 56.0, 15);
	ballManager->AddHole(61.0, 614.0, 15);
	ballManager->AddHole(635.0, 626.0, 15);
	ballManager->AddHole(1207.0, 614.0, 15);
	ballManager->AddHole(1207.0, 58.0, 15);

	//create a cue
	ballManager->CreateCue();

}

//poll for sdl events
void Game::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

}


void Game::update() {

	//run physics loop 10 times each frame for accuracy
	for (int i = 0; i < 10; i++)
	{
		ballManager->updatePhysics();
	}
	ballManager->update();

}


void Game::render() {

	renderer->Clear();
    glClear(GL_COLOR_BUFFER_BIT);

    table->draw();

    ballManager->drawBalls();

	ballManager->drawCue();

    SDL_GL_SwapWindow(window);

}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game Cleaned\n";

}

