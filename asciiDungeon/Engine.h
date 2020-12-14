#pragma once
#include "libtcod.hpp"


class Actor;
class Map;



class Engine {
public:
	TCODList<Actor*> actors;
	Actor* player;
	Map* map;
	int fovRadius;

	// screen data
	int screenWidth;
	int screenHeight;
	TCOD_key_t lastKey;

	enum GameStatus {
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT,
	}gameStatus;


	Engine(int screenWidth, int screenHeight);
	~Engine();

	void update();
	void render();
	void sendToBack(Actor* actor);

private:
	bool computeFov;
};

extern Engine engine;