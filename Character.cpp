#include "Character.h"


Character::Character(void)
{
	velocity.x=0;
	velocity.y=0;
}

Character::Character(const char* name)
{
	sprite->setName(name);    // file name , getting our picture
	velocity.x=0;
	velocity.y=0;
}

Character::Character(int x,int y, int w, int h,SDL_Renderer* render,const char* name) // character that would actualy be called
{
	ren=render;
	sprite=new Sprite(x,y,w,h,ren,name);     
	velocity.x=0;
	velocity.y=0;
}


Character::~Character(void)
{
}

void Character::loadSprite(SDL_Renderer* ren)
{
	sprite->LoadSprite(ren);
}
           // basically call the sprite for everything

void Character::renderSprite(SDL_Texture* target)
{
	sprite->renderSprite(target);
}

void Character::setSpriteName(const char* name)
{
	sprite->setName(name);
}


void Character::Update()
{
	sprite->UpdateDestination(velocity.x,velocity.y);     // make it move

}
