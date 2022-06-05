#include <SDL.h>
#include "Game.h"
#include <iostream>
using namespace std;

Game* game = nullptr;

const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 780;

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


    vec2 position = vec2(700.0f, 100.0f);
    float radius = 10.0f;

    float vertices[] = {
        // positions       
         position.x+radius, position.y+radius, 0.0f,
         position.x+radius, position.y-radius, 0.0f,
         position.x-radius, position.y-radius, 0.0f,
         position.x-radius, position.y+radius, 0.0f,
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

	Shader * shader = Game::assetManager->GetShader("circle");

	unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

	unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	shader->Bind();

    mat4 MVP = glm::ortho(0.0f, Game::screenSize->x, Game::screenSize->y, 0.0f);

	while (game->isRunning) {
		
		frameStart = SDL_GetTicks();

		game->getInputState();
		game->handleEvents();
		//game->update();
		
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		shader->Bind();

		glUniformMatrix4fv(glGetUniformLocation(shader->m_RendererID, "MVP"), 1, GL_FALSE, &MVP[0][0]);

		glm::vec3 col = glm::vec3(1.0f, 0.1f, 0.1f);
		glUniform3fv(glGetUniformLocation(shader->m_RendererID, "color"), 1, glm::value_ptr(col));

		glm::vec2 res = glm::vec2(Game::screenSize->x, Game::screenSize->y);
		glUniform2fv(glGetUniformLocation(shader->m_RendererID, "resolution"), 1, glm::value_ptr(res));

		glm::vec2 centerPos = glm::vec2(position.x, Game::screenSize->y - position.y);
		glUniform2fv(glGetUniformLocation(shader->m_RendererID, "center"), 1, glm::value_ptr(centerPos));

		glUniform1f(glGetUniformLocation(shader->m_RendererID,"uRadius"), radius);

		shader->Bind();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		game->render();
		

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}
	game->clean();
	
	return 0;

}