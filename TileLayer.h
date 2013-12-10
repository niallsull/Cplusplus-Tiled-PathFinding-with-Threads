#ifndef TILELAYER_H
#define TILELAYER_H
#include "Sprite.h"
#include <vector>
#include <string>

class TileLayer
{
public:
	TileLayer(void);
	~TileLayer(void);

	string name;
	int layerWidth;
	vector<int> gids;
};

#endif
