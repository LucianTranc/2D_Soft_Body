#pragma once
#include <map>
#include <string>
#include "Vector2D.h"
#include <SDL.h>
#include "Shader.h"

class AssetManager
{

public:

	AssetManager();
	~AssetManager();

	void AddShader(std::string id, const char* path);

	Shader* GetShader(std::string id);

private:
	std::map<std::string, Shader*> shaders;
	
};