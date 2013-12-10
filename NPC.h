#ifndef NPC_H
#define NPC_H
#include "Character.h"
#include "Tile.h"
#include "CollideTile.h"
#include "PathNode.h"

class NPC : public Character
{
public:
	NPC(void);
	NPC(int,int,int,int,SDL_Renderer*,const char*);
	~NPC(void);
	void Update();
	vector<PathNode*> path;
	void createPath(SDL_Rect*,int,int,vector<CollideTile*>);
	void getNeighbours(vector<CollideTile*>);

};

#endif

