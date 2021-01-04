#pragma once
class Ai {
public:
	virtual void update(Actor* owner) = 0;
	bool canAttack(int x, int y);
	virtual ~Ai() {};
};

class PlayerAi : public Ai {
public:
	void update(Actor* owner);
	void handleActionKey(Actor* owner, int ascii);

protected:
	Actor* chooseFromInventory(Actor* owner);

private:
	bool moveOrAttack(Actor* owner, int targetx, int targety);
};

class MonsterAi : public Ai {
public:
	void update(Actor* owner);
protected:
	void moveOrAttack(Actor* owner, int targetx, int targety);
	int moveCount;
	static const int TRACKING_TURNS = 3;
	
};