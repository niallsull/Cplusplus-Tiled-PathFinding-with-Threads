#include "ContentManager.h"

ContentManager* ContentManager:: instance;

ContentManager::ContentManager(void)
{
}


ContentManager* ContentManager::getInstance()      // bog standard singleton get instance
{  
	if(instance==NULL)
	{
		instance =new ContentManager();
	}

	return instance;

}

ContentManager::~ContentManager(void)
{
}

SDL_Texture* ContentManager::loadSprite(const char* name,SDL_Renderer* ren)
{
	if(!(spriteDictionary.count(name)==0))        // if count is not 0, then we have it already sur
	{
		return spriteDictionary.find(name)->second;
	}

	SDL_Surface* surface=IMG_Load(name);         // else , make it and add it

	SDL_Texture* texture=SDL_CreateTextureFromSurface(ren,surface);

	spriteDictionary.insert(make_pair(name,texture));

	SDL_FreeSurface(surface);

	return texture;

}
