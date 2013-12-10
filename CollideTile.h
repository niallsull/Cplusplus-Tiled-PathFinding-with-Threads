#ifndef COLLIDETILE_H
#define COLLIDETILE_H
#include <SDL.h>

class CollideTile
{
public:
	CollideTile(void);
	CollideTile(int,bool);
	~CollideTile(void);

	SDL_Rect tile;

	bool collidable;
	int cost;
};


#endif
