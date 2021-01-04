#pragma once

struct Tile {
	bool explored;
	Tile() : explored(false) {}
};

class Map
{
public:

	static const int ROOM_MAX_SIZE = 12;
	static const int ROOM_MIN_SIZE = 6;
	static const int MAX_ROOM_MONSTERS = 3;
	static const int MAX_ROOM_ITEMS = 2;

	int width, height;

	// construcotr and destructor
	Map(int width, int height);
	~Map();

	// check for collision
	bool isWall(int x, int y) const;
	bool canWalk(int x, int y) const;

	// Add monster
	void addMonster(int x, int y);

	// F O V
	bool isInFov(int x, int y) const;
	bool isExplored(int x, int y) const;
	void computeFov();
	// --

	void addItem(int x, int y);

	void render() const;
protected:
	Tile* tiles;
	friend class BspListener;

	TCODMap* map;
	
	void dig(int x1, int y1, int x2, int y2);
	void createRoom(bool first, int x1, int y1, int x2, int y2);

	void setWall(int x, int y);
};

