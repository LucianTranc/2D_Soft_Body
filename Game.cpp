#include "Game.h"
#include "Vector2D.h"
#include <sstream>
#include <cmath>
#include <OpenGL/gl3.h>
#include "Renderer.h"

//initialize static variables
SDL_Event Game::event;
AssetManager* Game::assetManager = new AssetManager();
ObjectManager* Game::objectManager = new ObjectManager();
bool Game::isRunning = false;
Vector2D* Game::screenSize = new Vector2D();
Renderer* Game::renderer = new Renderer();
const Uint8* Game::keystates = nullptr;
int Game::mousex = 0;
int Game::mousey = 0;

Game::Game() {}
Game::~Game() {}

//initialize the game
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
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

	//enable OpenGl blending and set a blending function
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_LINE_SMOOTH));
    GLCall(glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST));

	isRunning = true;

	screenSize->x = (float)width;
	screenSize->y = (float)height;

	loadAssets();
    
	//create all the balls, edges and holes
    createBalls();

	printf("Version:  %s\n", glGetString(GL_VERSION));	
}


void Game::loadAssets()
{
	//load the shaders
    assetManager->AddShader("line", "shaders/line.shader");
    assetManager->AddShader("circle", "shaders/circle.shader");
}

void Game::createBalls()
{
	objectManager->AddSoftBody(550.0f, 50.0f, 18.0f, 15, 15, 2.0f, 0.0001f, 7.0f, 3.0f);

	objectManager->AddEdge(0.0, 0.0, Game::screenSize->x, 0.0, 25.0);
	objectManager->AddEdge(Game::screenSize->x, 0.0, Game::screenSize->x, Game::screenSize->y, 25.0);
	objectManager->AddEdge(Game::screenSize->x, Game::screenSize->y, 0.0, Game::screenSize->y, 25.0);
	objectManager->AddEdge(0.0, Game::screenSize->y, 0.0, 0.0, 25.0);

	objectManager->AddEdge(80.0, 100.0, 500.0, 600.0, 30.0);
	objectManager->AddEdge(900.0, 600.0, 1300.0, 200.0, 30.0);

	objectManager->AddBall(200.0f, 100.0f, 60.0f, 0.0055f);
}

//poll for sdl events
void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}


void Game::update()
{
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

	objectManager->drawEdges();
    objectManager->drawBalls();
	objectManager->drawSprings();
	objectManager->drawLines();
	objectManager->drawCircles();

    SDL_GL_SwapWindow(window);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game Cleaned\n";
}

