#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>

using std::string;
using std::vector;
class Actor;
class TunnelMan;
class Earth;
class GoldNugget;
class Barrel;
class Boulder;
class Protestor;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
		ticksFromBegin = 0;
	}

	// MUST BE COMPLETED
	virtual int init();



	// MUST BE COMPLETED
	virtual int move();

	void SpawnBoulder(Actor *);
	void SpawnGoldOil(Actor*);
	void SpawnConsumable(Actor*);
	
	void coordinateGen(int& x, int & b);
	void coordinateGenEmpty(int& x, int & y);

	int getTicks() const;

	void setTicks(int a);

	void SpawnObject(Actor* a);

	void dig();
	// MUST BE COMPLETED
	virtual void cleanUp();

	


	string MakeHeader(int health, int water, int gold, int oilleft, int sonars);


	vector<Actor*> theList() {
		return objectlist;
	}

	TunnelMan* thePlayer() {
		return player;
	}

	// We also have access to these coming from GameWorld
	/*
	unsigned int getLives() const;
	void decLives();
	void incLives();
	unsigned int getScore() const;
	unsigned int getLevel() const;
	void increaseScore(unsigned int howMuch);
	void setGameStatText(string text);
	bool getKey(int& value);
	void playSound(int soundID);
	*/
	Earth* earth[64][64];
private:
	vector<Actor*> objectlist;
	
	TunnelMan* player;
	
	int ticksFromBegin;



};

#endif // STUDENTWORLD_H_
