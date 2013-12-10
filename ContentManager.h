#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <SDL.h>
#include <map>
#include "Sprite.h"
#include <string>
using namespace std;

class ContentManager
{
public:
	~ContentManager(void);
	static ContentManager* getInstance();
	SDL_Texture* loadSprite(const char*,SDL_Renderer*);
	map<const char*,SDL_Texture*> spriteDictionary;

private:
	ContentManager(void);
	static ContentManager* instance;
};

#endif
