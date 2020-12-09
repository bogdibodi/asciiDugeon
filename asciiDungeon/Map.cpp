#include "Map.h"
#include "libtcod.hpp"
#include "Actor.h"
#include "BspListener.h"
#include "Engine.h"

#include <iostream>



	Map::Map(int width, int height) 
		: width(width)
		, height(height)
	{
		tiles = new Tile[width * height];
		TCODBsp bsp(0, 0, width, height);
		bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
		BspListener listener(*this);
		bsp.traverseInvertedLevelOrder(&listener, NULL);
	}

	Map::~Map() {
		delete[] tiles;
	}
	bool Map::isWall(int x, int y) const {
		return !tiles[x + y * width].canWalk;
	}
	
	void Map::setWall(int x, int y) {
		tiles[x + y * width].canWalk = false;
	}
	
	


	void Map::dig(int x1, int y1, int x2, int y2) {
		if (x2 < x1) {
			int tmp = x2;
			x2 = x1;
			x1 = tmp;
		}
		if (y2 < y1) {
			int tmp = y2;
			y2 = y1;
			y1 = tmp;
		}


		for (int tilex = x1; tilex <= x2; tilex++) {
			for (int tiley = y1; tiley <= y2; tiley++) {
				tiles[tilex + tiley * width].canWalk = true;
			}
		}
	}

	void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
		dig(x1, y1, x2, y2);
		if (first) {
			//put player in freshly created room
			engine.player->x = (x1 + x2) / 2;
			engine.player->y = (y1 + y2) / 2;
		}
		else {
			TCODRandom* rng = TCODRandom::getInstance();
			if (rng->getInt(0, 3) == 0) {
				engine.actors.push(new Actor((x1 + x2) / 2, (y1 + y2) / 2, '@',
					TCODColor::yellow));
			}
		}
	}

	void Map::render() const {
		static const TCODColor darkWall(0, 0, 100);
		static const TCODColor darkGround(150, 50, 50);


		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				TCODConsole::root->setCharBackground(x, y, isWall(x, y) ? darkWall : darkGround);
				
			}
		}
	}