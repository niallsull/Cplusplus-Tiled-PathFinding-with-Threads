#ifndef NPCFACTORY_H
#define NPCFACTORY_H
#include "NPC.h"

class NPCFactory
{
public:
	NPCFactory(void);
	~NPCFactory(void);

	NPC* makeNPC(int,int,int,int,SDL_Renderer*,const char*);
	NPC* makeNPC();

};

#endif

