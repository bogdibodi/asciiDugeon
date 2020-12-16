#pragma once
class Gui {
public:
	static const int PANEL_HEIGHT = 7;
	static const int BAR_WIDTH = 20;

	static const int MSG_X = BAR_WIDTH + 2;
	static const int MSG_HEIGHT = PANEL_HEIGHT - 1;


	Gui();
	~Gui();

	void render();
	void message(const TCODColor& col, const char* text, ...);
protected:
	TCODConsole* con;
	struct Message {
		char* text;
		TCODColor col;
		Message(const char* text, const TCODColor& col);
		~Message();
	};
	TCODList<Message*> log;

	void renderMouseLook();
	void renderBar(int x, int y, int width, const char* name,
		float value, float maxValue, const TCODColor& barColor,
		const TCODColor& backColor);
};