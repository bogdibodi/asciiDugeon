#include <stdio.h>
#include "main.h"


Engine::Engine(int screenWidth, int screenHeight)
    : fovRadius(10)
    , gameStatus(STARTUP)
    , screenWidth(screenWidth)
    , screenHeight(screenHeight)

{

	TCODConsole::initRoot(screenWidth,screenHeight, "ASCII DUNGEON", false);
	player = new Actor(40, 25, '@',"Player", TCODColor::white);
    player->destructible = new PlayerDestructible(30, 2, "your cadaver");
    player->attacker = new Attacker(5);
    player->ai = new PlayerAi;
	actors.push(player);
	map = new Map(80, 43);
    gui = new Gui();
    gui->message(TCODColor::red, "Prepare to die.");
}
Engine::~Engine() {
	actors.clearAndDelete();
	delete map;
    delete gui;
}

void Engine::update() {
    TCOD_key_t key;
    if (gameStatus == STARTUP) map->computeFov();
    gameStatus = IDLE;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE,
         &lastKey, &mouse);
    player->update();
    if (gameStatus == NEW_TURN) {
        for (Actor** iterator = actors.begin();
            iterator != actors.end(); iterator++) {
            Actor* actor = *iterator;
            if (actor != player) {
                actor->update();
            }
        }
    }


} 
void Engine::render() {
    TCODConsole::root->clear();
    // draw the map
    map->render();
    // draw the actors
    for (Actor** iterator = actors.begin();
        iterator != actors.end(); iterator++) {
        Actor* actor = *iterator;
        if (map->isInFov(actor->x, actor->y)) {
            actor->render();
        }
    }
    player->render();
    gui->render();
    TCODConsole::root->printf(1, screenHeight - 2, "HP : %d / %d",
        (int)player->destructible->hp, (int)player->destructible->maxHp);

}
void Engine::sendToBack(Actor* actor) {
    actors.remove(actor);
    actors.insertBefore(actor, 0);
}


