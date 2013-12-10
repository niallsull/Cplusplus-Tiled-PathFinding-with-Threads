#include "TileEngine.h"




TileEngine::TileEngine(void)
{
}

TileEngine::TileEngine(const char* name,SDL_Renderer* render)
{
	docname=name;           // what we parsing today then
	ren=render;
}

TileEngine::~TileEngine(void)
{
}


void TileEngine::parseEngine()
{
	XMLDocument doc;
	doc.LoadFile(docname);     // sure we'll make a start


	vector<int> tileRanges;
	XMLElement* map=doc.FirstChildElement("map");
	XMLElement* tileset=map->FirstChildElement("tileset");       // self explained , get the tileset element  etc

	TileSet* ts=new TileSet(atoi(tileset->Attribute("firstgid")),tileset->Attribute("name"),atoi(tileset->Attribute("tilewidth")),atoi(tileset->Attribute("tileheight")),tileset->FirstChildElement("image")->Attribute("source"),atoi(tileset->FirstChildElement("image")->Attribute("width")),atoi(tileset->FirstChildElement("image")->Attribute("height")));
	tilesets.push_back(ts);
	tileRanges.push_back(atoi(tileset->Attribute("firstgid")));
	while(tileset->NextSiblingElement("tileset")!=NULL)
	{
		tileset=tileset->NextSiblingElement();
		int firstGid=atoi(tileset->Attribute("firstgid"));
		string name=tileset->Attribute("name");
		int tw=atoi(tileset->Attribute("tilewidth"));
		int th=atoi(tileset->Attribute("tileheight"));
		string source=tileset->FirstChildElement("image")->Attribute("source");
		int iw=atoi(tileset->FirstChildElement("image")->Attribute("width"));
		int ih=atoi(tileset->FirstChildElement("image")->Attribute("height"));
		ts=new TileSet(firstGid,name,tw,th,source,iw,ih);
		tilesets.push_back(ts);
		tileRanges.push_back(firstGid);
	}

	XMLElement* image=0;     
	int imageWidth=0;
	int imageHeight=0;
	const char* imageS;
	string imageName;
	int spacing=0;
	int margin=0;

	bool isometric=false;        // for orthag or iso

	string isoString=(map->Attribute("orientation"));
	if(isoString=="isometric")
	{
		isometric=true;                   //  well is it isometric then tommy
	}
	if(isometric==false)
	{
		cout << isometric << endl;
	}

	if(!(tileset->Attribute("source")==NULL))            // desert keeps the image data in another file
	{
		XMLDocument imageSource;												// just checking if we need to go another file for images or not
		imageSource.LoadFile(tileset->Attribute("source"));
		XMLElement* tilesetI=imageSource.FirstChildElement("tileset");
		image=tilesetI->FirstChildElement("image");

		
		imageWidth=atoi(image->Attribute("width"));
		imageHeight=atoi(image->Attribute("height"));
		imageS=image->Attribute("source");
		imageName=imageS;
		if(tilesetI->Attribute("spacing")!=NULL)
			spacing=atoi(tilesetI->Attribute("spacing"));

		if(tilesetI->Attribute("margin")!=NULL)
			margin=atoi(tilesetI->Attribute("margin"));
	}
	else
	{

		image=tileset->FirstChildElement("image");           // get image height width, what picture is etc
		imageWidth=atoi(image->Attribute("width"));
		imageHeight=atoi(image->Attribute("height"));
		imageS=image->Attribute("source");
		imageName=imageS;

		if(tileset->Attribute("spacing")!=NULL)
			spacing=atoi(tileset->Attribute("spacing"));

		if(tileset->Attribute("margin")!=NULL)
			margin=atoi(tileset->Attribute("margin"));
	}
	vector<XMLElement*> layers;
	int tlc=0;

	imageS=imageName.c_str();        // make sure its a const char*
	XMLElement* layer=map->FirstChildElement("layer");
	
	

	tilelayers.push_back(new TileLayer());
	string nam=layer->Attribute("name");
	tilelayers.at(tlc)->name=nam;
	int lw=atoi(layer->Attribute("width"));
	tilelayers.at(tlc)->layerWidth=lw;

	layers.push_back(layer);

	XMLElement* data=layer->FirstChildElement("data");
	XMLElement* tile=data->FirstChildElement("tile");
	tilelayers.at(tlc)->gids.push_back(atoi(tile->Attribute("gid")));
	while(tile->NextSiblingElement("tile")!=NULL)
	{
		tile=tile->NextSiblingElement();
		
		tilelayers.at(tlc)->gids.push_back(atoi(tile->Attribute("gid")));
	}

	

	while(layer->NextSiblingElement("layer")!=NULL)      // basically put all the layers together
	{
		layer=layer->NextSiblingElement();
		tlc++;
		XMLElement* data=layer->FirstChildElement("data");
		XMLElement* tile=data->FirstChildElement("tile");
		tilelayers.push_back(new TileLayer());
		nam=layer->Attribute("name");
		tilelayers.at(tlc)->name=nam;
		lw=atoi(layer->Attribute("width"));
		tilelayers.at(tlc)->layerWidth=lw;
		tilelayers.at(tlc)->gids.push_back(atoi(tile->Attribute("gid")));
		while(tile->NextSiblingElement("tile")!=NULL)
		{
			tile=tile->NextSiblingElement();
			tilelayers.at(tlc)->gids.push_back(atoi(tile->Attribute("gid")));
		}

		
		
		layers.push_back(layer);
	}


	/*
	for(int j=0;j<layers.size();j++)       // and go through all the layers
	{

		XMLElement* data=layers.at(j)->FirstChildElement("data");

		int width=atoi(layers.at(j)->Attribute("width"));
		int height=atoi(layers.at(j)->Attribute("height"));

		int tileWidth=atoi(map->Attribute("tilewidth"));
		int tileHeight=atoi(map->Attribute("tileheight"));


		int numColumns=imageWidth / tileWidth;
		int numRows=imageHeight / tileHeight;

		


		XMLElement* tile=data->FirstChildElement("tile");       // start getting tile data

		int destColumn=0;
		int destRow=0;
		Tile* s;
		// gid start at 1, so we need to minus 1 off they're value
			if(isometric)
					s=new Tile(((atoi(tile->Attribute("gid"))-1 ) % numColumns) , (((atoi(tile->Attribute("gid"))-1 )  / numColumns)), tileWidth,tileHeight, imageS,destColumn+(width),destRow,ren,margin, spacing,isometric);
				else
					s=new Tile(((atoi(tile->Attribute("gid"))-1 ) % numColumns) , (((atoi(tile->Attribute("gid"))-1 )  / numColumns)), tileWidth,tileHeight, imageS,destColumn,destRow,ren,margin, spacing,isometric);
			// simple modulus and integer division to pick off where in the sheet we are taking the image	
		

		tiles.push_back(s); // and add

		//imageSource=image->Attribute("source");

		for(int i=1;i<(width*height);i++)  // and now repeat for all the other tiles
		{
			tile=tile->NextSiblingElement();

			destColumn++;

			if(destColumn==width){
				destRow++;
				destColumn=0;
			}

			if(atoi(tile->Attribute("gid"))!=0)
			{
				if(isometric)
					s=new Tile(((atoi(tile->Attribute("gid"))-1 ) % numColumns) , (((atoi(tile->Attribute("gid"))-1 )  / numColumns)), tileWidth,tileHeight, imageS,destColumn+(width),destRow,ren,margin, spacing,isometric);
				else
					s=new Tile(((atoi(tile->Attribute("gid"))-1 ) % numColumns) , (((atoi(tile->Attribute("gid"))-1 )  / numColumns)), tileWidth,tileHeight, imageS,destColumn,destRow,ren,margin, spacing,isometric);
				tiles.push_back(s);
				//sprites.push_back(s);

			}

		}

	}

	return tiles;
	*/
}


vector<Sprite*> TileEngine::getSpriteLayer()
{
	return sprites;
}                                     // pretty much not gonna be used again

bool TileEngine::hasSpriteLayer(int i)
{
	
	return true;
	
	return false;
}

vector<TileLayer*> TileEngine::getTileLayers()
{
	return tilelayers;
}

vector<TileSet*> TileEngine::getTileSets()
{
	return tilesets;
}
