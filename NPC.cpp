#include "NPC.h"

// inheriting from character
NPC::NPC(void)
{
}


NPC::NPC(int x,int y, int w, int h,SDL_Renderer* render,const char* name)
{
	ren=render;
	sprite=new Sprite(x,y,w,h,ren,name);    // same as character
	velocity.x=0;
	velocity.y=0;
}

NPC::~NPC(void)
{
}

void NPC::Update()
{



	sprite->UpdateDestination(velocity.x,velocity.y);



	if(sprite->animate==true)    // just check the animation
		sprite->Animate();

	if(path.size()!=0)
	{
		int x=path.at(path.size()-1)->position.x;
		int y=path.at(path.size()-1)->position.y;

		if( (x==sprite->getDestination()->x) && (y==sprite->getDestination()->y) )
		{
			path.pop_back();
			velocity.x=0;
			velocity.y=0;
		}

		if(x!=sprite->getDestination()->x)
		{
			if(x<sprite->getDestination()->x)
				velocity.x=-2;
			if(x>sprite->getDestination()->x)
				velocity.x=2;

		}

		if(y!=sprite->getDestination()->y)
		{
			if(y<sprite->getDestination()->y)
				velocity.y=-2;
			if(y>sprite->getDestination()->y)
				velocity.y=2;

		}
	}

}




void NPC::getNeighbours(vector<CollideTile*> collidetiles)
{
	// check tiles each way if collidable, 4 directions

}
