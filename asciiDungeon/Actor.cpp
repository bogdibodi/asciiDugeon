#include "Actor.h"
#include "libtcod.hpp"	
#include "Engine.h"
#include "Map.h"

	Actor::Actor(int x, int y, int ch,const char *name, const TCODColor& col)
		: x(x)
		, y(y)
		, ch(ch)
		, col(col)
		, name(name)
	{}


	void Actor::render() const {
		TCODConsole::root->setChar(x, y, ch);
		TCODConsole::root->setCharForeground(x, y, col);		
}

	void Actor::update() {
		printf("The %s growls\n", name);
	}

	bool Actor::moveOrAttack(int x, int y) {
		if (engine.map->isWall(x, y)) return false;

		for (Actor** iterator = engine.actors.begin();
			iterator != engine.actors.end(); iterator++) {
			Actor* actor = *iterator;
			if (actor->x == x && actor->y == y) {
				printf("The %s laugh at puny efforts to attack him", actor->name);
				return false;
			}
			this->x = x;
			this->y = y;
			return true;
		}
	}