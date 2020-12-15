#include <stdio.h>
#include "main.h"

Destructible::Destructible(float maxHp, float defense, const char *corpseName)
	: maxHp(maxHp)
	, hp(maxHp)
	, defense(defense)
	, corpseName(corpseName)
{}

float Destructible::takeDamage(Actor* owner, float damage) {
	damage -= defense;
	if (damage > 0) {
		hp -= damage;
		if (hp <= 0) {
			die(owner);
		}
	}
	else {
		damage = 0;
	}
	return damage;
}
MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char* corpseName) :
	Destructible(maxHp, defense, corpseName) {
}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char* corpseName) :
	Destructible(maxHp, defense, corpseName) {
}

void Destructible::die(Actor* owner) {
	// make the corpse
	owner->ch = '%';
	owner->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->blocks = false;

	engine.sendToBack(owner);
}
void MonsterDestructible::die(Actor* owner) {
	printf("%s is dead\n", owner->name);
	Destructible::die(owner);
}
void PlayerDestructible::die(Actor* owner) {
	printf("You died!");
	engine.gameStatus = Engine::DEFEAT;
}
