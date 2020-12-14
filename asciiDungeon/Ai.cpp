#include <stdio.h>
#include "main.h"

void PlayerAi::update(Actor* owner) {
	if (owner->destructible && owner->destructible->isDead())
		return;

    int dx = 0, dy = 0;
    switch (engine.lastKey.vk) {
    case TCODK_UP: dy = -1; break;
    case TCODK_DOWN: dy = 1; break;
    case TCODK_LEFT: dx = -1; break;
    case TCODK_RIGHT: dx = 1; break;
    default:break;
    }
    if (dx != 0 || dy != 0) {
        engine.gameStatus = Engine::NEW_TURN;
        if (moveOrAttack(owner, owner->x + dx, owner->y + dy)) {
            engine.map->computeFov();
        }
    }
}
bool PlayerAi::moveOrAttack(Actor* owner, int targetx, int targety) {
    if (engine.map->isWall(targetx, targety)) return false;
    // search for living actors;
    for (Actor** iterator = engine.actors.begin();
        iterator != engine.actors.end(); iterator++) {
        Actor* actor = *iterator;
        if (actor->destructible && !actor->destructible->isDead()
            && actor->x == targetx && actor->y == targety) {
            owner->attacker->attack(owner, actor);
            return false;
        }
    }
    // look for corpses
    for (Actor** iterator = engine.actors.begin();
        iterator != engine.actors.end(); iterator++) {
        Actor* actor = *iterator;
        if (actor->destructible && actor->destructible->isDead()
            && actor->x == targetx && actor->y == targety) {
            printf("There's a %s here", actor->name);
        }
    }
    owner->x = targetx;
    owner->y = targety;
    return true;

}

void MonsterAi::update(Actor* owner) {
    if (owner->destructible && owner->destructible->isDead()) {
        return;
    }

    if (engine.map->isInFov(owner->x, owner->y)) {
        moveOrAttack(owner, engine.player->x, engine.player->y);
    }

}

bool Ai::canAttack(int x, int y) {
    int targetx = engine.player->x;
    int targety = engine.player->y;

    if ((targetx == x - 1 || targetx == x + 1 || targetx == x) && (targety == y - 1 || targety == y + 1 || targety == y) )
        return true;
    
    return false;
}



void MonsterAi::moveOrAttack(Actor* owner, int targetx, int targety) {
    int dx = targetx - owner->x;
    int dy = targety - owner->y;
    float distance = sqrtf(dx * dx * dy * dy);

    if (distance >= 2) {
        dx = (int)(round(dx / distance));
        dy = (int)(round(dy / distance));
    }

    if (engine.map->canWalk(owner->x + dx, owner->y + dy)) {
        owner->x += dx;
        owner->y += dy;
    }
    else if (owner->attacker && canAttack(owner->x, owner->y)) {
        owner->attacker->attack(owner, engine.player);
    }

}

