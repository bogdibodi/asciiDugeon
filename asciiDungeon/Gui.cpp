#pragma warning(disable : 4996)
#include "main.h"
#include "stdarg.h"

Gui::Gui() {
	con = new TCODConsole(engine.screenWidth, PANEL_HEIGHT);
}
Gui::~Gui() {
	delete con;
	log.clearAndDelete();
}
Gui::Message::Message(const char* text, const TCODColor& col) :
	text(strdup(text)), col(col) {
}

Gui::Message::~Message() {
	free(text);
}

void Gui::message(const TCODColor& col, const char* text, ...) {
	// make the text
	va_list ap;
	char buf[128];
	va_start(ap, text);
	vsprintf(buf, text, ap);
	va_end(ap);

	//
	char* lineBegin = buf;
	char* lineEnd;
	do {
		// make room for new msg
		if (log.size() == MSG_HEIGHT) {
			Message* toRemove = log.get(0);
			log.remove(toRemove);
			delete toRemove;
		}
		// detect EOL
		lineEnd = strchr(lineBegin, '\n');
		if (lineEnd) {
			*lineBegin = '\0';
		}
		// add new msg to log
		Message* msg = new Message(lineBegin, col);
		log.push(msg);
		// go to next line
		lineBegin = lineEnd + 1;
	} while (lineEnd);


}
void Gui::renderBar(int x, int y, int width, const char* name,
	float value, float maxValue, const TCODColor& barColor,
	const TCODColor& backColor) {
	// fill the background
	con->setDefaultBackground(backColor);
	con->rect(x, y, width, 1, false, TCOD_BKGND_SET);

	int barWidth = (int)(value / maxValue * width);
	if (barWidth > 0) {
		// draw the bar
		con->setDefaultBackground(barColor);
		con->rect(x, y, barWidth, 1, false, TCOD_BKGND_SET);
	}
	// print text on top of the bar
	con->setDefaultForeground(TCODColor::white);
	con->printEx(x + width / 2, y, TCOD_BKGND_NONE, TCOD_CENTER,
		"%s : %g/%g", name, value, maxValue);
}


void Gui::render() {
	//clear first
	con->setDefaultBackground(TCODColor::black);
	con->clear();

	// draw bar
	renderBar(1, 1, BAR_WIDTH, "HP", engine.player->destructible->hp,
		engine.player->destructible->maxHp, TCODColor::lightRed, TCODColor::darkerRed);

	// draw message log
	int y = 1;
	float colorCoef = 0.4f;
	for (Message** it = log.begin(); it != log.end(); it++) {
		Message* message = *it;
		con->setDefaultForeground(message->col);
		con->print(MSG_X, y, message->text);
		y++;
		if (colorCoef < 1.0f) {
			colorCoef += 0.3f;
		}
	}
	renderMouseLook();
	// blit the GUI
	TCODConsole::blit(con, 0, 0, engine.screenWidth, PANEL_HEIGHT, TCODConsole::root,
		0, engine.screenHeight - PANEL_HEIGHT);
}
void Gui::renderMouseLook() {
	if (!engine.map->isInFov(engine.mouse.cx, engine.mouse.cy)) {
		// if mouse is out of fov, nothing to render
		return;
	}
	char buf[128] = "";
	bool first = true;
	for (Actor** it = engine.actors.begin(); it != engine.actors.end(); it++) {
		Actor* actor = *it;
		// find actors under the mouse cursor
		if (actor->x == engine.mouse.cx && actor->y == engine.mouse.cy) {
			if (!first) {
				strcat(buf, ", ");
			}
			else {
				first = false;
			}
			strcat(buf, actor->name);
		}
	}
	// display the list of actors under the mouse cursor
	con->setDefaultForeground(TCODColor::lightGrey);
	con->print(1, 0, buf);
}
