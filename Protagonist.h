#ifndef PROTAGONIST_H
#define PROTAGONIST_H
#include "Character.h"

class Protagonist : public Character
{
public:
	Protagonist(void);
	Protagonist(int,int,int,int,SDL_Renderer*,const char*);
	~Protagonist(void);
	SDL_Rect* top;
	SDL_Rect* left;
	SDL_Rect* right;
	SDL_Rect* bottom;
	void Update();
	void move(int,int);
};

#endif 

