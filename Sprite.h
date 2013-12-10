#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "tinyxml2.h"
#include <iostream>
using namespace tinyxml2;
using namespace std;


class Sprite
{
public:
	Sprite(void);
	Sprite(int,int,int,int,const char*,int,int,SDL_Renderer*,int,int);
	Sprite(int,int,int,int,SDL_Renderer*,const char*);
	~Sprite(void);
	void LoadSprite(SDL_Renderer* );
	void renderSprite(SDL_Texture*);
	void move(int,int);
	void setName(const char* );
	void UpdateDestination(int,int);
	void UpdateSource(int,int);
	SDL_Rect* getDestination();
	bool animate;
	void Animate();
	int animWidth;
	int frameX;
	int animateCounter;

	int cameraX;
	int cameraY;

	bool Collinding(SDL_Rect*);
	void cleanUp();

private:
	SDL_Texture* texture;
	SDL_Rect* source;
	SDL_Rect* destination;
	SDL_Rect* drawDestion;
	SDL_Surface* surface;
	const char* image;
	SDL_Renderer* ren;
};

#endif
