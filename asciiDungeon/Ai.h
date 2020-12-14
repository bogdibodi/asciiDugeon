#pragma once
class Ai {
public:
	virtual void update(Actor* owner) = 0;
	bool canAttack(int x, int y);
};

class PlayerAi : public Ai {
public:
	void update(Actor* owner);
	

private:
	bool moveOrAttack(Actor* owner, int targetx, int targety);
};

class MonsterAi : public Ai {
public:
	void update(Actor* owner);
protected:
	void moveOrAttack(Actor* owner, int targetx, int targety);
	
};