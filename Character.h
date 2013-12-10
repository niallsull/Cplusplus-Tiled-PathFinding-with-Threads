#ifndef CHARACTER_H
#define CHARACTER_H
#include "Sprite.h"



class Character
{
public:
	struct Vector2
	{
		int x;
		int y;
	};

	Character(void);
	Character(const char* name);
	Character(int,int,int,int,SDL_Renderer*,const char*);
	virtual ~Character(void)=0;
	Sprite* sprite;
	void setSpriteName(const char*);
	void loadSprite(SDL_Renderer* ren);
	void renderSprite(SDL_Texture*);
	Vector2 velocity;
	void Update();
	SDL_Renderer* ren;
};

#endif
