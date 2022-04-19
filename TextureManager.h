#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

class TextureManager {

public:
	static Texture * LoadTexture(const char* texturePath, float w, float h, float iw, float ih);

};