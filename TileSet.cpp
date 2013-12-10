#include "TileSet.h"


TileSet::TileSet(void)
{
}

TileSet::TileSet(int first,string name,int tw,int th,string s,int w, int h)
{
	firstGid=first;
	name=name;
	tileWidth=tw;
	tileHeight=th;
	imageSource=s;
	imageWidth=w;
	imageHeight=h;
}

TileSet::~TileSet(void)
{
}
