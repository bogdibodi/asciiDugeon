#pragma once
class BspListener : public ITCODBspCallback {
	private:
		Map& map; // a map to dig
		int roomNum; // room number
		int lastx = 0 , lasty = 0; // center of the last room
	public:
		
		BspListener(Map& map);
		bool visitNode(TCODBsp *node, void* userData);
};


