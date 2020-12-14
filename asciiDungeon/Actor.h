#pragma once
#include "libtcod.hpp"


class Actor
{
public:
	int x, y; // position
	int ch; // ASCII code
	TCODColor col; //color
	const char* name;



	Actor(int x, int y, int ch, const char* name, const TCODColor &col);
	void update();
	bool moveOrAttack(int x, int y);
	void render() const;
};
