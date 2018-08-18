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
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{

	}

	// MUST BE COMPLETED
	virtual int init();



	// MUST BE COMPLETED
	virtual int move();

	void SpawnOilBoulderBarrel(Actor *);

	void SpawnObject(Actor* a);


	// MUST BE COMPLETED
	virtual void cleanUp();

	Earth*  getEarth();


	string MakeHeader(int health, int water, int gold, int oilleft, int sonars);




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

private:
	vector<Actor*> objectlist;
	TunnelMan* player;
	Earth* earth[64][64];




};

#endif // STUDENTWORLD_H_
