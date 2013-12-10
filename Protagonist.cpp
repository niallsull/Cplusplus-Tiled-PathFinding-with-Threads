#include "Protagonist.h"


Protagonist::Protagonist(void)    // inherits from character
{
}

Protagonist::Protagonist(int x,int y, int w, int h,SDL_Renderer* render,const char* name)
{
	ren=render;
	sprite=new Sprite(x,y,w,h,ren,name);            // same as character again
	velocity.x=0;
	velocity.y=0;
	top=new SDL_Rect();
	top->x=x+2;
	top->y=y-2;
	top->h=4;
	top->w=w-4;
	left=new SDL_Rect();
	left->x=x-2;
	left->y=y+2;
	left->h=h-4;
	left->w=4;
	right=new SDL_Rect();
	right->x=x+w-2;
	right->y=y+2;
	right->h=h-4;
	right->w=4;
	bottom=new SDL_Rect();
	bottom->x=x+2;
	bottom->y=y+h-2;
	bottom->h=4;
	bottom->w=w-4;
}

Protagonist::~Protagonist(void)
{
}

void Protagonist::Update()
{

	
	sprite->UpdateDestination(velocity.x,velocity.y);

	if(sprite->animate==true)            // chack animation of sprite , could be seen as redundant checking , i dunno
		sprite->Animate();

}

void Protagonist::move(int x, int y)
{
	sprite->UpdateDestination(x,y);
	top->x+=x;
	top->y+=y;

	right->x+=x;
	right->y+=y;

	left->x+=x;
	left->y+=y;

	bottom->x+=x;
	bottom->y+=y;

}
