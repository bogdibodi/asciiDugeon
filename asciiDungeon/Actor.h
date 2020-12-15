#pragma once

// make a sword enemy that after its killed you can weild it


class Actor
{
public:
	int x, y; // position
	int ch; // ASCII code
	TCODColor col; //color
	
	const char* name; // char name
	bool blocks; // check if player can walk over
	Attacker* attacker; // dmg dealer
	Destructible* destructible; //something that breaks
	Ai* ai;



	Actor(int x, int y, int ch, const char* name, const TCODColor &col);
	~Actor() {
		delete attacker;
		delete destructible;
		delete ai;
	};

	void update();
	// bool moveOrAttack(int x, int y); 
	// ^ Now Handled by the AI
 	void render() const;
};

