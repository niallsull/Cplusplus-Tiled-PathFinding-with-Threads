#ifndef TILE_H
#define TILE_H
#include "Sprite.h"

class Tile
{
public:
	Tile(void);
	~Tile(void);
	Tile(int,int,int,int,const char*,int,int,SDL_Renderer*,int,int,bool);
	void DrawTile(SDL_Texture*);
	Sprite* sprite;
	bool isometric;

};

#endif

