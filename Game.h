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
#include "BallManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Edge.h"
#include "Table.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
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

	static Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static AssetManager *assetManager;
	static TextureManager *textureManager;
	static BallManager *ballManager;
	static Vector2D *screenSize;
	static Table *table;
	glm::mat4 projection;
    VertexArray * va;
	VertexBuffer * vb;
    VertexBufferLayout * layout;
	IndexBuffer * ib;
	Shader * shader;
	Texture * texture;

private:

	SDL_Window* window;

};

