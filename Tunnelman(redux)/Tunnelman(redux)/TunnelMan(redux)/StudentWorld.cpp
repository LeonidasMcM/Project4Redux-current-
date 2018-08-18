#include "StudentWorld.h"
#include "Actor.h"
#include"GameConstants.h"
#include <string>
#include<vector>
#include<iterator>


class GraphObject;
GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp




string StudentWorld::MakeHeader(int health, int water, int gold, int oilleft, int sonars)
{

	string temp = "Lvl: " + std::to_string(getLevel()) + " Lives: " + std::to_string(getLives()) + " Hlth: "
		+ std::to_string(health * 20) + "% Wtr: " + std::to_string(water) + " Gld: "
		+ std::to_string(gold) + " Oil Left: " + std::to_string(oilleft) + " Sonar: "
		+ std::to_string(sonars) + " Scr: " + std::to_string(getScore());
	return temp;

}





//A.Initialize the data structures used to keep track of your game’s virtual world
//16
//B.Construct a new oil field that meets the requirements stated in the section below
//(filled with Earth, Barrels of oil, Boulders, Gold Nuggets, etc.)
//C.Allocate and insert a valid Tunnelman object into the game world at the proper
//location
int StudentWorld::init()
{
	// Creating the player
	player = new TunnelMan(this);

	// Create Earth
	
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			earth[i][j] = new Earth(i, j,this);
		}
}
	for(int i=0;i<64;i++)
		for (int j = 59; j < 64; j++) {
			earth[i][j]->setVisible(false);
		}
	for (int i = 30; i<35; i++)
		for (int j = 4; j < 59; j++) {
			earth[i][j]->setVisible(false);
		}

		
	// Amount of Boulders
	int level = getLevel();
	int B = std::min(level / 2 + 2, 9);


	// Amount of Gold
	int G = std::max(5 - level / 2, 2);

	// Amount of Oil Barrels
	int L = std::min(2 + level, 21);

	// Setting the initial game header text
	setGameStatText(MakeHeader(player->getHealth(), player->getSquirts(), 0, L, 0));
	
	
	return GWSTATUS_CONTINUE_GAME;
	
}

int StudentWorld::move(){
	// Counter for current # of barrels
	int level = getLevel();
	int L = std::min(2 + level, 21);


	if (getLives() == 0)
		return GWSTATUS_PLAYER_DIED;
	else{





		// Player takes action
		player->doSomething();

		// Removing the earth as the TunnelMan moves
		earth[player->getX()][player->getY()]->setVisible(false);
		earth[player->getX()+1][player->getY()]->setVisible(false);
		earth[player->getX()+2][player->getY()]->setVisible(false);
		earth[player->getX() + 3][player->getY()]->setVisible(false);

		earth[player->getX()][player->getY() + 1]->setVisible(false);
		earth[player->getX()+1][player->getY()+1]->setVisible(false);
		earth[player->getX()+2][player->getY()+1]->setVisible(false);
		earth[player->getX() + 3][player->getY() + 1]->setVisible(false);
		
		earth[player->getX()][player->getY()+2]->setVisible(false);
		earth[player->getX() + 1][player->getY()+2]->setVisible(false);
		earth[player->getX() + 2][player->getY()+2]->setVisible(false);
		earth[player->getX() + 3][player->getY()+2]->setVisible(false);

		earth[player->getX()][player->getY() + 3]->setVisible(false);
		earth[player->getX() + 1][player->getY() + 3]->setVisible(false);
		earth[player->getX() + 2][player->getY() + 3]->setVisible(false);
		earth[player->getX() + 3][player->getY() + 3]->setVisible(false);

		

		// Consumables and Protestors take actions
		for (int i = 0; i < objectlist.size(); i++)
			objectlist[i]->doSomething();

		if (player->getHealth() == 0) {
			decLives();
			return GWSTATUS_PLAYER_DIED;
		}
		else {
			int i=0;
			while(i<objectlist.size()) {

				if (!objectlist[i]->GetStatus()) {
					
					delete objectlist[i];
					objectlist.erase(objectlist.begin()+i);
					i--;
				}
				i++;
			}
		}


		// If all the Barrels are found end the level
		if (player->foundBarrels() == L) {
			
			return GWSTATUS_FINISHED_LEVEL;
		}

		

		// Update text
		setGameStatText(MakeHeader(player->getHealth(), player->getSquirts(), 0, L-player->foundBarrels(), 0));

		return GWSTATUS_CONTINUE_GAME;
	}

}

void StudentWorld::SpawnOilBoulderBarrel(Actor *)
{
}

void StudentWorld::SpawnObject(Actor * a){
	objectlist.push_back(a);
}



void StudentWorld::cleanUp()
{
	// Deleting earth
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			delete earth[i][j];
		}
	}
	// Deleting Objects
	while (objectlist.size() > 0) {
			delete objectlist[0];
			objectlist.erase(objectlist.begin());
		}


}

Earth* StudentWorld::getEarth()
{
	return earth[0][0];
}

	







