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
ObjectManager* Game::objectManager = new ObjectManager();
bool Game::isRunning = false;
Vector2D* Game::screenSize = new Vector2D();
Renderer* Game::renderer = new Renderer();
Background* Game::background = new Background();
const Uint8* Game::keystates = nullptr;
int Game::mousex = 0;
int Game::mousey = 0;

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
    
	//initialize the background
	background->init();

	//create all the balls, edges and holes
    createBalls();

	printf("Version:  %s\n", glGetString(GL_VERSION));
	
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
    assetManager->AddShader("line", "shaders/line.shader");

	//enable OpenGl blending and set a blending function
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

}

void Game::createBalls() {

	/* objectManager->AddBall(935.0, 335.0, 13.0, 1, "white");

	objectManager->AddBall(935.0 + 24.0*1.0, 335.0 + 14.0*1.0, 13.0, 2, "white");
	objectManager->AddBall(935.0 + 24.0*1.0, 335.0 - 14.0*1.0, 13.0, 3, "white");

	objectManager->AddBall(935.0 + 24.0*2.0, 335.0 - 14.0*2.0, 13.0, 4, "white");
	objectManager->AddBall(935.0 + 24.0*2.0, 335.0 - 14.0*0.0, 13.0, 5, "white");
	objectManager->AddBall(935.0 + 24.0*2.0, 335.0 + 14.0*2.0, 13.0, 6, "white");

	objectManager->AddBall(935.0 + 24.0*3.0, 335.0 - 14.0*3.0, 13.0, 7, "white");
	objectManager->AddBall(935.0 + 24.0*3.0, 335.0 - 14.0*1.0, 13.0, 8, "white");
	objectManager->AddBall(935.0 + 24.0*3.0, 335.0 + 14.0*1.0, 13.0, 9, "white");
	objectManager->AddBall(935.0 + 24.0*3.0, 335.0 + 14.0*3.0, 13.0, 10, "white");

	objectManager->AddBall(935.0 + 24.0*4.0, 335.0 - 14.0*4.0, 13.0, 11, "white");
	objectManager->AddBall(935.0 + 24.0*4.0, 335.0 - 14.0*2.0, 13.0, 12, "white");
	objectManager->AddBall(935.0 + 24.0*4.0, 335.0 + 14.0*0.0, 13.0, 13, "white");
	objectManager->AddBall(935.0 + 24.0*4.0, 335.0 + 14.0*2.0, 13.0, 14, "white");
	objectManager->AddBall(935.0 + 24.0*4.0, 335.0 + 14.0*4.0, 13.0, 15, "white"); */


	
	objectManager->AddSoftBody(0,0,0,0);


	objectManager->AddBall(350.0, 335.0, 13.0, "white");
	objectManager->AddBall(400.0, 335.0, 13.0, "white");
	objectManager->AddSpring(objectManager->balls[0], objectManager->balls[1]);


	//add edges to the ball manager

	//objectManager->AddEdge(0.0, 50.0, 1155.0, 50.0, 25.0);


	objectManager->AddEdge(0.0, 0.0, 1270.0, 0.0, 25.0);
	objectManager->AddEdge(1270, 0.0, 1270.0, 670.0, 25.0);
	objectManager->AddEdge(1270.0, 670.0, 0.0, 670.0, 25.0);
	objectManager->AddEdge(0.0, 670.0, 0.0, 0.0, 25.0);


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
	/* for (int i = 0; i < 10; i++)
	{
		objectManager->updatePhysics();
	} */
	objectManager->updatePhysics();
	objectManager->update();

}

void Game::getInputState()
{
    SDL_PumpEvents();
    keystates = SDL_GetKeyboardState(NULL); 
    SDL_GetMouseState(&mousex, &mousey);
}

void Game::render()
{

	renderer->SetClearColour(0.8f, 0.8f, 0.8f, 1.0f);

	renderer->Clear();

    //background->draw();

	objectManager->drawEdges();

    objectManager->drawBalls();

	objectManager->drawSprings();

	objectManager->drawLines();

    SDL_GL_SwapWindow(window);

}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game Cleaned\n";

}

