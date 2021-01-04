#pragma once


class Container {
public:
	int size; // 0 = no limit
	TCODList<Actor*> inventory;

	Container(int size);
	~Container();
	bool add(Actor* actor);
	void remove(Actor* actor);
};