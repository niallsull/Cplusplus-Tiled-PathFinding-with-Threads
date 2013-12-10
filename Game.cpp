#include "Game.h"
#include "`Debug.h"

using namespace std;

NPC* Game::npcArray[2];
vector<CollideTile*> Game::collideTiles;
PathMaker* Game::pm;
thread Game::path[2];

Game::Game(void)
{

}


Game::~Game(void)
{
}

void Game::Initialize(const char* title,int x,int y,int w, int h, int flags)
{

	
	window=SDL_CreateWindow(title,x,y,w,h,flags);               // window
	render=SDL_CreateRenderer(window,0,0);						// renderer
	player=new Protagonist(50,50,20,32,render,"charAnim.bmp");

	NPCfactory= NPCFactory();                        // plan was to have more npcs 

	player->sprite->animate=true;
	player->sprite->frameX=0;          // our player conatins animation
	player->sprite->animWidth=10;           //  so sort that out
	player->sprite->animateCounter=0;
	npcArray[1]=NPCfactory.makeNPC(1*32,12*32,32,32,render,"enemy.bmp"); 
	
	npcArray[0]=NPCfactory.makeNPC(12*32,1*32,32,32,render,"enemy.bmp");// enemy just a box
	drawTarget = SDL_CreateTexture(render,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,w*4,h*4);        // what we'll draw to screen
	buffTarget = SDL_CreateTexture(render,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,w*4,h*4);			// to clear our screen
	//GameTicks=SDL_GetTicks();  not used anymore
	destination=new SDL_Rect();     // where to draw our target
	destination->w=w*3;
	destination->h=h*3;
	destination->x=player->sprite->getDestination()->x+(w/2);             // start out in the middle of the screen
	destination->y=player->sprite->getDestination()->y+(h/2);			// kinda

	source=new SDL_Rect();
	source->x=0;
	source->y=0;
	source->w=w*3;
	source->h=h*3;


	 //pm=PathMaker(20,20,32,32,);
	// npc1->path=pm.createPath(player->sprite->getDestination(),npc1->sprite->getDestination(),collideTiles);
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );      // open up audio, straight out copy

	pm=new PathMaker(20,20,32,32,player->sprite->getDestination());
	updateEnemy=0;
	
	//pathMaker=thread(&Game::pathFinder);
	
}


void Game::LoadContent(const char* fileName)
{


	/*surface=SDL_LoadBMP("orc1.bmp");
	DEBUG_MSG("SURFACE LOADED");
	texture=SDL_CreateTextureFromSurface(render,surface);
	SDL_FreeSurface(surface);*/
	music = Mix_LoadMUS( "ambience_background_hum.wav" );    // music
	collide = Mix_LoadWAV("explosion.wav");   // play when hit the enemy
	keyBoardState=SDL_GetKeyboardState(NULL);   //  our keyboard
	te=new TileEngine(fileName,render);


	te->parseEngine();       /// where the hell do i put these tiles


	/*for(int i=0;i<tiles.size();i++)
	{
		tiles.at(i)->sprite->cameraX=cam.x;
		tiles.at(i)->sprite->cameraX=cam.x;
	}*/

	tileLayers=te->getTileLayers();
	tilesets=te->getTileSets();

	Mix_PlayMusic( music, -1 );      // bang out some tunes lad !
	fillTiles();
	fillCollision();


	//PathMaker::getInstance(20,20,32,32,player->sprite->getDestination());
	//pathMaker=thread(pm->RunAI);
	//paths=thread(&PathMaker::getInstance(20,20,32,23,player->sprite->getDestination())->RunAI);
	pathMaker =thread(&Game::pathFinder);
}

void Game::HandleEvents()
{
	SDL_Event event;


	 // could just be put in update, but sure

	if(SDL_PollEvent(&event))
	{
		switch(event.type){

		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_running=false;
				break;
			
			}

		}
	}

}


void Game::Render()
{
	SDL_RenderClear(render);       // blank canvas

	SDL_SetRenderTarget(render, drawTarget);          // draw to our texture first
	SDL_RenderCopy(render,buffTarget,NULL,NULL);       // make her go blank

	for(int i=0;i<tiles.size();i++)
	{

		tiles.at(i)->DrawTile(drawTarget);        // draw them tiles
	}

	for(int i=0;i<collisionTiles.size();i++)
	{

		collisionTiles.at(i)->DrawTile(drawTarget);        // draw them tiles
	}

	player->renderSprite(drawTarget);
	for(int i=0;i<2;i++)
	{
		npcArray[i]->renderSprite(drawTarget);
	}
	SDL_SetRenderTarget(render,NULL);           // back to main drawing
	SDL_RenderCopy(render,drawTarget,NULL,destination);      // and slap the texure on it
	SDL_RenderPresent(render);

}


void Game::Update()
{
	SDL_PumpEvents();                   // get the events going (update), to see changes in keyboard
	keyBoardState=SDL_GetKeyboardState(NULL);   // keyboard state


	if(keyBoardState[SDL_SCANCODE_UP])
	{
		player->move(0,-3);
		destination->y+=3;
	}

	if(keyBoardState[SDL_SCANCODE_DOWN])
	{
		player->move(0,3);
		destination->y-=3;
	}																		//  up down left right
																			//  ^    |
	if(keyBoardState[SDL_SCANCODE_LEFT])									//  |		 <-     ->
	{
		player->move(-3,0);
		destination->x+=3;
	}

	if(keyBoardState[SDL_SCANCODE_RIGHT])
	{
		player->move(3,0);
		destination->x-=3;
	}

	if(keyBoardState[SDL_SCANCODE_ESCAPE])
	{
		m_running=false;

	}


	player->Update();    // if veolicity was actually set
	npcArray[1]->Update();

	npcArray[0]->Update();
	/*updateEnemy++;

	if(updateEnemy>600)
	{
		npc1->path=pm.createPath(player->sprite->getDestination(),npc1->sprite->getDestination(),collideTiles);
		updateEnemy=0;
	}
*/
	/*if(npcArray[1]->path.size()==0)
		npcArray[1]->path=pm.createPath(npcArray[1]->sprite->getDestination(),collideTiles);

	if(npcArray[0]->path.size()==0)
		npcArray[0]->path=pm.createPath(npcArray[0]->sprite->getDestination(),collideTiles);*/

	bool colliding=player->sprite->Collinding(npcArray[0]->sprite->getDestination());

	for(int i=0;i<collisionTiles.size();i++)
	{
		if(isColliding(player->sprite->getDestination(),collisionTiles.at(i)->sprite->getDestination()))
		{
			//DEBUG_MSG("COLLIDING");
			handlePlayerCollide(i);
		}
			

	}
	   // check collision,   then go BOOM
	if(colliding)
		Mix_PlayChannel( -1, collide, 0 );


	
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::CleapUp()            // make everything zero  000000000000000000000000000000
{
	for(int i=0;i<sprites.size();i++)
	{
		tiles.at(i)->sprite->cleanUp();
		tiles.at(i)=0;

	}

	pathMaker.join();

	player->sprite->cleanUp();
	npcArray[1]->sprite->cleanUp();
	npcArray[0]->sprite->cleanUp();
	player=0;
	npcArray[1]=0;
	npcArray[0]=0;

	drawTarget=0;
	buffTarget=0;
	destination=0;
	source=0;
	te=0;
	keyBoardState=0;


	Mix_FreeChunk(collide);
	Mix_FreeMusic( music );
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();

}

void Game:: UnloadContent()
{
	window=0;
	render=0;
}

void Game::moveSpritesRight()
{
	for(int i=0;i<sprites.size();i++)
	{
		sprites.at(i)->move(3,0);
	}

}

void Game::moveSpritesLeft()
{
	for(int i=0;i<sprites.size();i++)
	{
		sprites.at(i)->move(-3,0);
	}

}

bool Game::isColliding(SDL_Rect* r1, SDL_Rect* r2)        // original collision, sprite based the same except using rects
{
	                                   // lazy foo basically
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	
	//Calculate the sides of rect A
	leftA = r1->x;
	rightA = r1->x + r1->w;
	topA = r1->y;
	bottomA = r1->y + r1->h;

	//Calculate the sides of rect B
	leftB = r2->x;
	rightB = r2->x + r2->w;
	topB = r2->y;
	bottomB = r2->y + r2->h;


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
	}																// just makes sure we're in it
															// don't care what way right now
	//If none of the sides from A are outside B
	return true;
}


void Game::fillTiles()
{
	int ts=0;
	int tl=0;
	for(int i=0;i<tileLayers.size();i++)
	{
		if(tileLayers.at(i)->name!="collision")
		{
			for(int j=tilesets.size()-1;j>=0;j--)
			{
				if((tileLayers.at(i)->gids.at(0)) >= (tilesets.at(j)->firstGid))
				{
					ts=j;
					tl=i;
				}
			}
		}
	}

	const char* source=tilesets.at(ts)->imageSource.c_str();
	int tileWidth=tilesets.at(ts)->tileWidth;
	int tileHeigth=tilesets.at(ts)->tileHeight;
	int imgWidth=tilesets.at(ts)->imageWidth;
	int imgHeight=tilesets.at(ts)->imageHeight;
	int lw=tileLayers.at(tl)->layerWidth;

	int numColumns=imgWidth / tileWidth;
	int numRows=imgHeight / tileHeigth;

	int destColumn=0;
	int destRow=0;

	for(int i=0; i<tileLayers.at(1)->gids.size();i++)
	{
		

		if(tileLayers.at(ts)->gids.at(i) !=0)
		{
			Tile* t=new Tile( ((tileLayers.at(1)->gids.at(i)-1 ) % numColumns) , (((tileLayers.at(1)->gids.at(i))-1 )  / numColumns), tileWidth,tileHeigth, source,destColumn,destRow,render,0, 0,false);
			tiles.push_back(t);
		}

		destColumn++;

		if(destColumn==lw){
			destRow++;
			destColumn=0;
		}
	}

}

void Game::fillCollision()
{
	int tl=0;

	for(int i=0;i<tileLayers.size();i++)
	{
		if(tileLayers.at(i)->name=="collision")
			break;

		tl++;
	}

	int ts;
	for(int j=tilesets.size()-1;j>=0;j--)
	{
			if((tileLayers.at(tl)->gids.at(0)) >= (tilesets.at(j)->firstGid))
			{
				ts=j;
				break;
			}
	}

	int lw=tileLayers.at(tl)->layerWidth;
	int collidable=tilesets.at(ts)->firstGid;

	int tileWidth=tilesets.at(ts)->tileWidth;
	int tileHeigth=tilesets.at(ts)->tileHeight;
	int imgWidth=tilesets.at(ts)->imageWidth;
	int imgHeight=tilesets.at(ts)->imageHeight;

	int numColumns=imgWidth / tileWidth;
	int numRows=imgHeight / tileHeigth;

	int destColumn=0;
	int destRow=0;
	
	for(int i=0;i<tileLayers.at(tl)->gids.size();i++)
	{
		CollideTile* ct = new CollideTile();
		ct->tile.x=destColumn*tileWidth;
		ct->tile.y=destRow*tileHeigth;
		ct->tile.h=tileHeigth;
		ct->tile.w=tileWidth;
		ct->collidable=false;

		if(tileLayers.at(tl)->gids.at(i) == collidable)
		{
			Tile* t=new Tile( ((tileLayers.at(1)->gids.at(i)-1 ) % numColumns) , (((tileLayers.at(1)->gids.at(i))-1 )  / numColumns), tileWidth,tileHeigth, "collision.png",destColumn,destRow,render,0, 0,false);
			collisionTiles.push_back(t);
			ct->collidable=true;
			
		}
		ct->cost=tileLayers.at(tl)->gids.at(i)-collidable-1;
		collideTiles.push_back(ct);

		destColumn++;

		if(destColumn==lw){
			destRow++;
			destColumn=0;
		}

	}

}


void Game::handlePlayerCollide(int i)
{
	if(isColliding(player->top,collisionTiles.at(i)->sprite->getDestination()))
	{
		DEBUG_MSG("TOP");
		player->move(0,3);
		destination->y-=3;
	}
	
	if(isColliding(player->left,collisionTiles.at(i)->sprite->getDestination()))
	{
		DEBUG_MSG("LEFT");
		player->move(3,0);
		destination->x-=3;
	}
	if(isColliding(player->right,collisionTiles.at(i)->sprite->getDestination()))
	{
		DEBUG_MSG("RIGHT");
		player->move(-3,0);
		destination->x+=3;
	}
	if(isColliding(player->bottom,collisionTiles.at(i)->sprite->getDestination()))
	{
		DEBUG_MSG("BOTTOM");
		player->move(0,-3);
		destination->y+=3;
	}


}

void Game::pathFinder()
{
	while(true)
	{
		for(int i=0;i<2;i++)
		{
			if(npcArray[i]->path.size()==0)
			{
				
				thread(pm->createPath,npcArray[i]->sprite->getDestination(),collideTiles,npcArray[i]->path);
			
			}
		}


	}

}
