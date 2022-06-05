#include "AssetManager.h"

AssetManager::AssetManager() {}
AssetManager::~AssetManager() {}

void AssetManager::AddShader(std::string id, const char* path)
{
	Shader * shader = new Shader(path);
	shaders.emplace(id, shader);
}


Shader* AssetManager::GetShader(std::string id)
{
	if (shaders[id])
	{
		shaders[id]->Bind();
		return shaders[id];
	}	
	
	return nullptr;
}