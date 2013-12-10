#include "NPCFactory.h"
 // not technically needed in this case, but we could spit out more npc
// in which case give enums for the way the move i suppose, something like that

NPCFactory::NPCFactory(void)
{
}


NPCFactory::~NPCFactory(void)
{
}

NPC* NPCFactory::makeNPC(int x,int y, int w, int h,SDL_Renderer* render,const char* name)  // factory is told what to make
{
	NPC* npc=new NPC(x,y,w,h,render,name);

	return npc;
}

NPC* NPCFactory::makeNPC()
{
	NPC* npc;
	npc->setSpriteName("enemy.bmp");   // or generic as can be enemy
	return npc;
}
