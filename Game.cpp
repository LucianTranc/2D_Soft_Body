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

	glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);

	isRunning = true;

	//load font library
	if (TTF_Init() == -1)
		std::cout << "Error : SDL_TTF" << std::endl;


	screenSize->x = (float)width;
	screenSize->y = (float)height;

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
    assetManager->AddTexture("ball1", "assets/blackcircle1.png", 26.0f, 26.0f, Game::screenSize->x, Game::screenSize->y);
    assetManager->AddTexture("ball2", "assets/blackcircle1.png", 50.0f, 50.0f, Game::screenSize->x, Game::screenSize->y);
    assetManager->AddTexture("ball3", "assets/blackcircle1.png", 30.0f, 30.0f, Game::screenSize->x, Game::screenSize->y);
    assetManager->AddTexture("black", "assets/bb_black.png", 26.0f, 26.0f, Game::screenSize->x, Game::screenSize->y);
    assetManager->AddTexture("white", "assets/bb_white.png", 26.0f, 26.0f, Game::screenSize->x, Game::screenSize->y);
    assetManager->AddShader("line", "shaders/line.shader");
    assetManager->AddShader("circle", "shaders/circle.shader");

	//enable OpenGl blending and set a blending function
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

}

void Game::createBalls() {

	//objectManager->AddSoftBody(500.0f, 150.0f, 50.0f, 7, 7);

	//objectManager->AddEdge(0.0, 0.0, Game::screenSize->x, 0.0, 25.0);
	//objectManager->AddEdge(Game::screenSize->x, 0.0, Game::screenSize->x, Game::screenSize->y, 25.0);
	//objectManager->AddEdge(Game::screenSize->x, Game::screenSize->y, 0.0, Game::screenSize->y, 25.0);
	//objectManager->AddEdge(0.0, Game::screenSize->y, 0.0, 0.0, 25.0);

	//objectManager->AddEdge(100.0, 100.0, 500.0, 600.0, 25.0);
	//objectManager->AddEdge(900.0, 600.0, 1300.0, 200.0, 25.0);

	//objectManager->AddCircle(100.0f, 100.0f, 15.0f);

	circle1 = new Circle(500.0f, 500.0f, 100.0f);
	circle2 = new Circle(700.0f, 900.0f, 200.0f);
	circle3 = new Circle(100.0f, 500.0f, 50.0f);

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

	//renderer->SetClearColour(0.8f, 0.8f, 0.8f, 1.0f);

	//renderer->Clear();

    //background->draw();

	//objectManager->drawEdges();

    //objectManager->drawBalls();

	circle1->draw();
	circle2->draw();
	circle3->draw();

	//objectManager->drawSprings();

	//objectManager->drawLines();

	//objectManager->drawCircles();


    SDL_GL_SwapWindow(window);

}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game Cleaned\n";

}

