#include "tinyxml2.h"
#include <vector>
#include <iostream>
#include "Game.h"
#include "`Debug.h"
#include <SDL.h>
using namespace tinyxml2;
using namespace std;



int main(int argc, char* args[])
{



	Game* game=new Game();

	game->Initialize("TileEngine",20,20,500,500,0);

	const char* file="CollisionMap.tmx";         // change as appropriate

	game->LoadContent(file);
	int FPS=30;                  // fps rate
	Uint32 start=SDL_GetTicks();            // used in calculating fps
	while(game->IsRunning())
	{
		//game->HandleEvents();
		game->Update();
		game->Render();

		if(1000/FPS>SDL_GetTicks()-start)                       // if running fast,   banf on delay
		{
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));              // else we're behind
		}
		start=SDL_GetTicks();                                    // re initialise
	}


	DEBUG_MSG("calling cleanup");
	game->UnloadContent();
	game->CleapUp();                       // let's clean this mother


	cin.get();
	return 0;
}
