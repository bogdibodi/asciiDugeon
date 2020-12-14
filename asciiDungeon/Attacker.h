#pragma once
class Attacker {
public:
	float power; // how much hitpoints

	Attacker(float power);
	void attack(Actor* owner, Actor* target);
};