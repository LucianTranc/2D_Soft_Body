#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "AssetManager.h"
#include "TextureManager.h"
#include "Ball.h"
#include "ObjectManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Edge.h"
#include "Background.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Line.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class Game

{

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void loadAssets();
	void createBalls();
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	void getInputState();

	static Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static AssetManager *assetManager;
	static TextureManager *textureManager;
	static ObjectManager *objectManager;
	static Vector2D *screenSize;
	static Background *background;
	static int mousex;
	static int mousey;
	static const Uint8* keystates;
/* 	glm::mat4 projection;
    VertexArray * va;
	VertexBuffer * vb;
    VertexBufferLayout * layout;
	IndexBuffer * ib;
	Shader * shader;
	Texture * texture; */

private:

	SDL_Window* window;

};

