#ifndef PATHMAKER_H
#define PATHMAKER_H
#include "PathNode.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include "CollideTile.h"
#include "PriorityQueue.h"
#include <stack>
#include <thread>
using namespace std;

class PathMaker
{
public:
	
	

	~PathMaker(void);

	static void createPath(SDL_Rect*,vector<CollideTile*>,vector<PathNode*>);
	void RunAI();

	static void addNeighbours(PriorityQueue*,vector<CollideTile*>,PathNode*,SDL_Rect*);

	static int height;
	static int width;
	static int tileW;
	static int tileH;
	static bool busy;
	static SDL_Rect* dest;
	static vector<PathNode*> openList;
	static vector<PathNode*> closedList;

	static int calcManhattan(int, int, SDL_Rect*);
	static int findTileCost(int,vector<CollideTile*>);
	static int findPathCost(PathNode*);

	static bool isOnClosed(PathNode*);
	static PathNode* minOpen();
	//thread t;
	

	PathMaker(int,int,int,int,SDL_Rect*);
	PathMaker();
	

};

#endif
