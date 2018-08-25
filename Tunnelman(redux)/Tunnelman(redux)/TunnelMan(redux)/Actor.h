

#ifndef ACTOR_H_
#define ACTOR_H_



#include "StudentWorld.h"
#include "GraphObject.h"
#include"GameConstants.h"
#include <algorithm>

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// THESE ALL HAVE ACCESS TO
/*

GraphObject(int imageID, int startX, int startY,
DIRECTION startDirection, float size = 1.0,
unsigned int depth = 0);
void setVisible(bool shouldIDisplay);
void getX() const;
void getY() const;
void moveTo(int x, int y);
DIRECTION getDirection() const; // Directions: up, down, left, right
void setDirection(DIRECTION d); // Directions: up, down, left, right

These image ids
IMID_PLAYER // for the Tunnelman
IMID_PROTESTER // a regular protester
IMID_HARD_CORE_PROTESTER // a hardcore protester
IMID_WATER_SPURT // for a squirt of water from the Tunnelman
IMID_BOULDER
IMID_BARREL // a barrel of oil
IMID_EARTH // a 1x1 square of earth
IMID_GOLD // a gold nugget
IMID_SONAR // a sonar kit
IMID_WATER_POOL // a water pool to refill the squirt gun

Key ID's

KEY_PRESS_LEFT
KEY_PRESS_RIGHT
KEY_PRESS_UP
KEY_PRESS_DOWN
KEY_PRESS_SPACE
KEY_PRESS_ESCAPE
KEY_PRESS_TAB
‘z’
‘Z’

*/

class Actor : public GraphObject {
	friend class StudentWorld;
public:
	Actor(int ID, int x, int y, Direction input, float size, int depth, StudentWorld* world) :GraphObject(ID, x, y, input, size, depth) {
		status = true;
		thisWorld = world;
		this->setVisible(true);
	}
	bool GetStatus();
	virtual void doSomething() = 0;
	StudentWorld* getWorld() const;
	void setStatus(bool input);

	virtual bool tooClose(Actor*);

	virtual bool isBoulder() {
		return false;
	}

	


private:
	bool status;
	StudentWorld* thisWorld;


};

class TunnelMan :public Actor {
	friend class StudentWorld;
public:
	
	TunnelMan(StudentWorld * world) :Actor(TID_PLAYER, 30, 60, right, 1.0, 0, world) {
		health = 5;
		squirts = 5;
		sonars = 0;
		stunduration = 0;
		gold = 0;
		sonarstate = false;
	};
	int getHealth();
	int getSquirts();
	int getGold()
	{
		return gold;
	};
	int getSonars() {
		return sonars;
	}
	void doSomething();
	void useSonar();
	void setHealth(int a) {
		health = a;
	};


	void foundBarrel() {
		barrels++;
	};
	int foundBarrels();
	void foundGold() {
		gold++;
	}
	
	void squirt();
	void dropGold();

	bool sonarStatus() {
		return sonarstate;
	}

	void setStun(int a) {
		stunduration = a;
	};
	void incSonars() {
		sonars++;
	}
	void incWater() {
		squirts = squirts + 5;
	}
private:
	int stunduration;
	int squirts;
	int sonars;
	int gold;
	int health;
	int barrels;
	bool sonarstate;
	int sonarticks;



};


class Earth :public Actor {
public:
	Earth(int x, int y, StudentWorld* world) :Actor(TID_EARTH, x, y, right, 0.25, 3, world) {
		visible = true;
	};
	bool tooClose(Actor*);
	void doSomething() {};
	bool visible;

};

class Boulder :public Actor {
public:
	Boulder(int x, int y, StudentWorld* world) :Actor(TID_BOULDER, x, y, down, 1.0, 1, world) {
		Stability = true;
		ticks = 20;
		initialchange = false;
	}
	bool IsStable();
	bool isBoulder(){
		return true;
	}
	void doSomething();
private:
	bool Stability;
	int ticks;
	bool initialchange;
};




class Squirt : public Actor {
public:
	Squirt(int x, int y, Direction input, StudentWorld* world) :Actor(TID_WATER_SPURT, x, y, input, 1.0, 1, world) {
		moves = 4;

	}

	void doSomething();
private:
	int moves;

};

class Barrel :public Actor {
public:
	Barrel(int x, int y, StudentWorld* world) : Actor(TID_BARREL, x, y, right, 1.0, 2, world) {};
	bool tooClose(Actor*);
	void sighted();
	void doSomething();
};

class GoldNugget :public Actor {
public:
	GoldNugget(int x, int y, bool pickable,  StudentWorld* world) :Actor(TID_GOLD, x, y, right, 1.0, 2, world) {
		if (pickable) {
			setVisible(false);
			perminance = true;
		}
		if (!pickable) {
			setVisible(true);
			perminance = false;
			ticks = 150;
		}
	}
	
	
	bool tooClose(Actor*);
	void sighted();
	void doSomething();

private:
	bool pickable;
	bool perminance;
	int ticks;
};

class Consumable :public Actor {
public:
	Consumable(int x, int y, int currentlevel, int ID, StudentWorld* world) :Actor(ID, x, y, right, 1.0, 2, world) {
		int temp = 300 - 10 * currentlevel;
		ticks = std::max(100, temp);
	}
	void tickDec();
	
	virtual void doSomething() {};
	int getTicks() {
		return ticks;
	}
private:
	int ticks;
	

};

class SonarKit :public Consumable {
public:
	SonarKit(int x, int y, int currentlevel, StudentWorld* world) : Consumable(x, y, currentlevel, TID_SONAR, world) {

	}
	void doSomething();
};

class WaterPool :public Consumable {
public:
	WaterPool(int x, int y, int currentlevel, StudentWorld* world) : Consumable(x, y, currentlevel, TID_WATER_POOL, world) {

	}
	void doSomething();
};

class Protestor :public Actor {
public:
	Protestor(int x, int y, int currentlevel, int ID, StudentWorld* world) :Actor(ID, x, y, left, 1.0, 0, world) {
		numtomove = 8 + rand() % 52;
		hitpoint = 5;
		leave = false;
		ticksToWaitBetweenMoves = std::max(0, 3 - currentlevel / 4);
		ticksleft = ticksToWaitBetweenMoves;
	}
	int getMoves();
	int getHitpoints();
	bool readyToLeave();
	virtual bool closeToTunnelman();
	void hurtProtestor(int damage);
	void changeTicksleft();
	void searchMaze();
	void doSomething();

private:
	int ticksToWaitBetweenMoves;
	int ticksleft;
	int numtomove;
	int hitpoint;
	bool leave;
};

class HARDCOREProtestor :public Protestor {
public:
	HARDCOREProtestor(int x, int y, int currentlevel, StudentWorld* world) :Protestor(x, y, currentlevel, TID_HARD_CORE_PROTESTER, world) {
		searchdistance = 16 + currentlevel * 2;
	};
	bool closeToTunnelman();
	void doSomething();

private:
	int searchdistance;
};


#endif // ACTOR_H_
