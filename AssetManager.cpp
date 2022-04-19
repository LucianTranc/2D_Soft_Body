#include "AssetManager.h"

//this class loads and stores textures and fonts

AssetManager::AssetManager()
{}

AssetManager::~AssetManager()
{}

//Load texture with the texture manager
void AssetManager::AddTexture(std::string id, const char* path, float w, float h, float iw, float ih)
{
	Texture * tex = TextureManager::LoadTexture(path, w, h, iw, ih);
	textures.emplace(id, tex);
}

//return the texture with the matching id, binding it in the process
Texture* AssetManager::GetTexture(std::string id)
{
	if (textures[id]) {
		textures[id]->Bind();
		return textures[id];
	}	
	return nullptr;
}

void AssetManager::SetActiveTexture(std::string id)
{
	textures[id]->Bind();
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}