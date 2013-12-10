#include "Sprite.h"
#include "ContentManager.h"

Sprite::Sprite(void)
{
	animate=false;
	cameraX=0;
	cameraY=0;
}

Sprite::Sprite(int col,int row,int width,int height, const char* name,int destCol,int destRow,SDL_Renderer* render,int margin,int spacing)
{
	source=new SDL_Rect();
	source->x=(width*col) + margin + (spacing*col);
	source->y=(height*row) + margin + (spacing*row);

	source->w=width;
	source->h=height;
	destination=new SDL_Rect();
	destination->x=destCol*width;
	destination->y=destRow*height;
	destination->w=width;
	destination->h=height;
	image=name;

	ren=render;
	LoadSprite(ren);
	animate=false;
	cameraX=0;
	cameraY=0;
	drawDestion=new SDL_Rect();
}

Sprite::Sprite(int x,int y,int wide,int high,SDL_Renderer* render,const char* name )
{
	destination=new SDL_Rect();
	source=new SDL_Rect();
	destination->h=high;
	destination->w=wide;
	destination->x=x;
	destination->y=y;

	source->x=0;
	source->y=0;
	source->w=wide;
	source->h=high;


	ren=render;
	image=name;

	LoadSprite(ren);

	animate=false;
	cameraX=0;
	cameraY=0;
	drawDestion=new SDL_Rect();
}

Sprite::~Sprite(void)
{
}


void Sprite::LoadSprite(SDL_Renderer* ren)
{

	texture=ContentManager::getInstance()->loadSprite(image,ren);
	/*
	surface=IMG_Load(image);
	//surface=SDL_LoadBMP(image);
	//surface=SDL_DisplayFormat(surface);
	if(!surface)
	{
	cout << image << endl;
	}
	//cout << image << endl;
	texture=SDL_CreateTextureFromSurface(ren,surface);

	//texture=SDL_CreateTextureFromSurface(render,surface);
	SDL_FreeSurface(surface);
	*/
}

void Sprite::renderSprite(SDL_Texture* target)
{

	drawDestion->x=destination->x - cameraX;
	drawDestion->y=destination->y - cameraY;
	drawDestion->h=destination->h;
	drawDestion->w=destination->w;
	//SDL_RenderCopy(render,texture,NULL,drawDestion);
	SDL_SetRenderTarget(ren, target);
	SDL_RenderCopy(ren,texture,source,destination);


	//cout << "render sprite" << endl;
}

void Sprite::move(int xMove,int yMove)
{
	destination->x=destination->x+xMove;

	destination->y=destination->y+yMove;
}


void Sprite::setName(const char* name)
{
	image=name;
}


void Sprite::UpdateDestination(int x,int y)
{
	destination->x+=x;
	destination->y+=y;
}


void Sprite::UpdateSource(int x,int y)
{
	source->x=x;
	source->y=y;
}

SDL_Rect* Sprite::getDestination()
{
	return destination;
}

void Sprite::Animate()
{

	animateCounter++;

	if(animateCounter==20){
		frameX++;
		animateCounter=0;
	}

	if(frameX==animWidth-1)
		frameX=0;

	source->x=source->w*frameX;
}

bool Sprite::Collinding(SDL_Rect* rect)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	SDL_Rect* thisRect=new SDL_Rect();

	thisRect->x=destination->x-cameraX;
	thisRect->y=destination->y-cameraY;
	thisRect->h=destination->h;
	thisRect->w=destination->w;


	//Calculate the sides of rect A
	leftA = rect->x;
	rightA = rect->x + rect->w;
	topA = rect->y;
	bottomA = rect->y + rect->h;

	//Calculate the sides of rect B
	leftB = drawDestion->x;
	rightB = drawDestion->x + drawDestion->w;
	topB = drawDestion->y;
	bottomB = drawDestion->y + drawDestion->h;


	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;


}

void Sprite::cleanUp()
{
	texture=0;
	source=0;
	destination=0;
	drawDestion=0;
	surface=0;
	image=0;
	ren=0;

}
