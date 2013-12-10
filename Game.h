#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "tinyxml2.h"
#include <string>
#include <iostream>
#include "Sprite.h"
#include "Character.h"
#include "NPCFactory.h"
#include "NPC.h"
#include "Protagonist.h"
#include "TileEngine.h"
#include "Tile.h"
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "CollideTile.h"
#include "PathMaker.h"
#include <thread>
using namespace std;
using namespace tinyxml2;

typedef struct Camera 
{ 
	float x, y; 
} Camera; 

class Game
{
public:
	Game(void);
	~Game(void);
	void HandleEvents();
	void Update();
	void Render();
	void Initialize(const char*,int,int,int,int,int);
	void CleapUp();
	bool IsRunning();
	void LoadContent(const char*);
	void UnloadContent();
	SDL_Renderer* render;
	SDL_Texture* drawTarget;
	SDL_Texture* buffTarget;
	SDL_Rect* destination;
	SDL_Rect* source;
	Protagonist* player;
	static NPC* npcArray[2];
	Camera cam;
	Mix_Music *music;
	Mix_Chunk *collide;

	static vector<CollideTile*> collideTiles;
	

private:
	bool m_running;
	SDL_Window* window;
	NPCFactory NPCfactory;
	void moveSpritesRight();
	void moveSpritesLeft();

	int GameTicks;

	TileEngine* te;
	vector<Sprite*> sprites;
	vector<Tile*> tiles;
	vector<TileLayer*> tileLayers;
	vector<TileSet*> tilesets;
	bool isColliding(SDL_Rect*, SDL_Rect*);
	const Uint8 *keyBoardState;
	vector<Tile*> collisionTiles;
	static PathMaker* pm;
	int updateEnemy;

	void fillTiles();
	void fillCollision();

	void handlePlayerCollide(int i);

	thread pathMaker;
	static thread path[2];

	static void pathFinder();
};

#endif
