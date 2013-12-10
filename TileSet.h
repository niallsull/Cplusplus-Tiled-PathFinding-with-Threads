#ifndef TILESET_H
#define TILESET_H
#include <string>
using namespace std;
class TileSet
{
public:
	TileSet(void);
	TileSet(int,string,int,int,string, int, int);
	~TileSet(void);

	int firstGid;
	string name;
	int tileWidth;
	int tileHeight;
	string imageSource;
	int imageWidth;
	int imageHeight;

};

#endif
