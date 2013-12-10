#ifndef TILEENGINE_H
#define TILEENGNE_H
#include "tinyxml2.h"
#include <vector>
#include <string>
#include "Sprite.h"
#include "Tile.h"
#include "TileSet.h"
#include "TileLayer.h"
using namespace std;
using namespace tinyxml2;

class TileEngine
{
public:
	TileEngine(void);
	TileEngine(const char*,SDL_Renderer*);
	~TileEngine(void);
	//XMLDocument* doc;
	const char* docname;

	void parseEngine();

	vector<Tile*> tiles;
	vector<Sprite*> sprites;         // originally no tiles, just sprites, tile introduces for isometric
	//vector<vector<Sprite>> spriteLayers;
	bool hasSpriteLayer(int);				// not used anymore
	vector<Sprite*> getSpriteLayer();		// not used anymore
	SDL_Renderer* ren;
	vector<TileSet*> tilesets;
	vector<TileLayer*> tilelayers;

	vector<TileSet*> getTileSets();
	vector<TileLayer*> getTileLayers();

};

#endif
