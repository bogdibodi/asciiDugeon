#pragma once
#include "libtcod.hpp"


class Actor
{
public:
	int x, y; // position
	int ch; // ASCII code
	TCODColor col; //color


	Actor(int x, int y, int ch, const TCODColor &col);
	void render() const;
};

