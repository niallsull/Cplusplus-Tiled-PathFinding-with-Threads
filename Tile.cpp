#include "Tile.h"

// originally didn't have tiles, just sprites, but iso kinda called for it in a way, iso or orthag tiles like
Tile::Tile(void)
{
}


Tile::~Tile(void)
{
}

Tile::Tile(int col,int row,int width,int height, const char* name,int destCol,int destRow,SDL_Renderer* render,int margin,int spacing, bool iso)
{
	sprite=new Sprite(col,row,width,height,name,destCol,destRow,render,margin,spacing); // just make a sprite as we always would 

	if(iso==true)
	{
		sprite->getDestination()->x=(sprite->getDestination()->x-sprite->getDestination()->y)/2;    // and convert if isometric
		sprite->getDestination()->y=(sprite->getDestination()->x+sprite->getDestination()->y) /2;

	}

}
// tile is pretty much sprite with a boolean


void Tile::DrawTile(SDL_Texture* target)
{
	sprite->renderSprite(target);   // call sprite draw 

}
