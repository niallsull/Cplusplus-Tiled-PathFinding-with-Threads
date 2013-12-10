#include "PathMaker.h"

bool PathMaker::busy;
vector<PathNode*> PathMaker::openList;
vector<PathNode*> PathMaker::closedList;
SDL_Rect* PathMaker::dest;
int PathMaker::height;
int PathMaker::width;
int PathMaker::tileH;
int PathMaker::tileW;

PathMaker::PathMaker()
{

}


PathMaker::PathMaker(int w,int h,int tw,int th,SDL_Rect* destination)
{
	width=w;
	height=h;
	tileW=tw;
	tileH=th;
	dest=destination;
	busy=false;

}

PathMaker::~PathMaker(void)
{
	
}

void PathMaker::RunAI()
{

	while(true)
	{
		while(busy==true)
		{

		}


		//do create path here

	}
	//return createPath();


}

void PathMaker::createPath(SDL_Rect* current, vector<CollideTile*> collisions,vector<PathNode*> path)
{
	while(busy==true)
	{

	}

	busy=true;

	openList.clear();

	closedList.clear();


	int x=current->x;
	int y=current->y;
	
	
	int manhattanX=(dest->x/tileW) - (x/tileW);
	int manhattanY=(dest->y/tileH) - (y/tileH);

	if(manhattanX<0)
		manhattanX*=-1;

	if(manhattanY<0)
		manhattanY*=-1;


	PathNode* curr=new PathNode(NULL,NULL,0,manhattanX+manhattanY,1,x,y);
	
	
	//return path;
	curr->cost=1;
	PriorityQueue* pq=new PriorityQueue();
	
	while( ((((dest->x)/tileW) == ((curr->position.x)/tileW)) && (((dest->y)/tileH) == ((curr->position.y)/tileH) )) ==false )
	{
		addNeighbours(pq,collisions,curr,dest);

		//curr=pq->nextNode();
		
		curr=minOpen();

		//runningCost+=curr->cost;

	}

	stack<PathNode*> pathStack;


	while(curr->previous!=NULL)
	{
		//add to stack
		path.push_back(curr);
		// current == previous;
		curr=curr->previous;
	}


	//for(int i=pathStack.size()-1;i>=0;i--)
	//{
	//	//add to list
	//	
	//	path.push_back(pathStack.top());
	//	pathStack.pop();
	//}
	busy=false;

	//return path;
}


void PathMaker::addNeighbours(PriorityQueue* queue,vector<CollideTile*> collisions, PathNode* c,SDL_Rect* target)
{

	// list +1 , -1 + width , - width, 
	//all outside tiles are coliidable, no worries about being on the edge
	// pointless checking

	int xpos=c->position.x / tileW;
	int ypos=c->position.y / tileH;

	int currentTile=(ypos*width) + xpos;
	
	//go left
	if(collisions.at(currentTile-1)->collidable==false)
	{
		// p=new PathNode(NULL,c,c->step+1,calcManhattan(c,target),c->position.x-tileW,c->position.y);
		//queue->AddNode(new PathNode(NULL,c,c->step+1,calcManhattan(c,target),c->position.x-tileW,c->position.y));

		if(isOnClosed(new PathNode(NULL,c,c->step+1,calcManhattan(c->position.x-tileW,c->position.y,target),(collisions.at(currentTile-1)->cost)+(c->cost),c->position.x-tileW,c->position.y))==false)
		{
			openList.push_back(new PathNode(NULL,c,c->step+1,calcManhattan(c->position.x-tileW,c->position.y,target),(collisions.at(currentTile-1)->cost)+(c->cost),c->position.x-tileW,c->position.y));
				
				openList.at(openList.size()-1)->cost=c->cost+(collisions.at(currentTile-1)->cost);
		}
	}

	//go right
	if(collisions.at(currentTile+1)->collidable==false)
	{
		// p=new PathNode(NULL,c,c->step+1,calcManhattan(c,target),c->position.x+tileW,c->position.y);
		//queue->AddNode(new PathNode(NULL,c,c->step+1,calcManhattan(c,target),c->position.x+tileW,c->position.y));
		if(isOnClosed(new PathNode(NULL,c,c->step+1,calcManhattan(c->position.x+tileW,c->position.y,target),collisions.at(currentTile+1)->cost+c->cost,c->position.x+tileW,c->position.y))==false)
		{
			openList.push_back(new PathNode(NULL,c,c->step+1,calcManhattan(c->position.x+tileW,c->position.y,target),collisions.at(currentTile+1)->cost+c->cost,c->position.x+tileW,c->position.y));
			openList.at(openList.size()-1)->cost=c->cost+(collisions.at(currentTile+1)->cost);
		}
	}

	//go up
	if(collisions.at(currentTile-width)->collidable==false)
	{
		// p=new PathNode(NULL,c,c->step+1,calcManhattan(c,target),c->position.x,c->position.y-tileH);
		//queue->AddNode(new PathNode(NULL,c,c->step+1,calcManhattan(c,target),c->position.x,c->position.y-tileH));
		if(isOnClosed(new PathNode(NULL,c,c->step+1,calcManhattan(c->position.x,c->position.y-tileH,target),collisions.at(currentTile-width)->cost+c->cost,c->position.x,c->position.y-tileH))==false)
		{
			openList.push_back(new PathNode(NULL,c,c->step+1,calcManhattan(c->position.x,c->position.y-tileH,target),collisions.at(currentTile-width)->cost+c->cost,c->position.x,c->position.y-tileH));
			openList.at(openList.size()-1)->cost=c->cost+(collisions.at(currentTile-width)->cost);		
		}
	}

	//go down
	if(collisions.at(currentTile+width)->collidable==false)
	{
		// p=new PathNode(NULL,c,c->step+1,calcManhattan(c,target),c->position.x,c->position.y+tileH);
		//queue->AddNode(new PathNode(NULL,c,c->step+1,calcManhattan(c,target),c->position.x,c->position.y+tileH));
		if(isOnClosed(new PathNode(NULL,c,c->step+1,calcManhattan(c->position.x,c->position.y+tileH,target),collisions.at(currentTile+width)->cost+c->cost,c->position.x,c->position.y+tileH))==false)
		{
			openList.push_back(new PathNode(NULL,c,c->step+1,calcManhattan(c->position.x,c->position.y+tileH,target),collisions.at(currentTile+width)->cost+c->cost,c->position.x,c->position.y+tileH));
			openList.at(openList.size()-1)->cost=c->cost+(collisions.at(currentTile+width)->cost);
		}
	}
}


int PathMaker::calcManhattan(int x,int y, SDL_Rect* target)
{
	int manhattanX=(x/tileW) - (target->x/tileW);
	int manhattanY=(y/tileH) - (target->y/tileH);

	if(manhattanX<0)
		manhattanX*=-1;

	if(manhattanY<0)
		manhattanY*=-1;


	return manhattanX+manhattanY;
}


bool PathMaker::isOnClosed(PathNode* node)
{
	

	for(int i=0;i<closedList.size();i++)
	{
		if( ((closedList.at(i)->position.x) ==(node->position.x)) && ((closedList.at(i)->position.y) ==(node->position.y)) && ( (closedList.at(i)->cost) == (node->cost))  )
		{
			return true;
		}

	}
	return false;
}


PathNode* PathMaker::minOpen()
{
	int min=9999;
	int minNode=0;

	for(int i=0;i<openList.size();i++)
	{
		if( (openList.at(i)->step) + (openList.at(i)->manhattan) +(openList.at(i)->cost) < min)
		{
			min=(openList.at(i)->step) + (openList.at(i)->manhattan)+(openList.at(i)->cost);
			minNode=i;
		}

	}

	if(isOnClosed(openList.at(minNode))==false)
	{
		closedList.push_back(openList.at(minNode));
	}
	closedList.push_back(openList.at(minNode));
	
	PathNode* returnNode=(openList.at(minNode));
	openList.erase(openList.begin()+minNode);

	return returnNode;

}

int PathMaker::findTileCost(int tile,vector<CollideTile*> tiles)
{

	return tiles.at(tile)->cost;
}

int PathMaker::findPathCost(PathNode* p)
{
	int cost=0;

	PathNode* temp=p;
	
	while(temp->previous!=NULL)
	{
		cost+=temp->cost;
		temp=temp->previous;
	}

	return cost;
}
