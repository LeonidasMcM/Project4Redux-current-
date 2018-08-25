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
			earth[i][j]->visible = false;
		}
	for (int i = 30; i<35; i++)
		for (int j = 4; j < 59; j++) {
			earth[i][j]->setVisible(false);
			earth[i][j]->visible = false;
		}

		
	// Amount of Boulders
	int level = getLevel();
	int B = std::min(level / 2 + 2, 9);
	int locX, locY;

	for (int i = 0; i < B; i++) {
		coordinateGen(locX, locY);
		Actor* temp = new Boulder(locX, locY, this);
		objectlist.push_back(temp);
		SpawnBoulder(temp);
		for (int k = temp->getX(); k <= temp->getX() + 3; k++)
			for (int l = temp->getY(); l <= temp->getY() + 3; l++) {
				earth[k][l]->setVisible(false);
				earth[k][l]->visible = false;
			}
	}

	// Amount of Gold
	int G = std::max(5 - level / 2, 2);
	for (int i = 0; i < G; i++) {
		coordinateGen(locX, locY);
		Actor* temp = new GoldNugget(locX, locY,true, this);
		objectlist.push_back(temp);
		SpawnGoldOil(temp);
	}

	// Amount of Oil Barrels
	int L = std::min(2 + level, 21);
	for (int i = 0; i < L; i++) {
		coordinateGen(locX, locY);
		Actor* temp = new Barrel(locX, locY, this);
		objectlist.push_back(temp);
		SpawnGoldOil(temp);
	}

	// Setting the initial game header text
	setGameStatText(MakeHeader(player->getHealth(), player->getSquirts(), 0, L, 0));
	
	
	return GWSTATUS_CONTINUE_GAME;
	
}

int StudentWorld::move(){
	// Counter for current # of barrels
	int level = getLevel();

	int TotalBarrels = std::min(2 + level, 21);


	if (getLives() == 0)
		return GWSTATUS_PLAYER_DIED;
	else{





		// Player takes action
		player->doSomething();

		// Removing the earth as the TunnelMan moves
		dig();
		

		

		// Consumables and Protestors take actions
		for (int i = 0; i < objectlist.size(); i++)
			objectlist[i]->doSomething();



		if (player->getHealth() == 0) {
			decLives();
			setTicks(0);
			return GWSTATUS_PLAYER_DIED;
		}
		else {
			int i=0;
			while(i<objectlist.size()) {

				if (!objectlist[i]->GetStatus()) {
					//deleting from managing vectors


					// deleteing from basic vector
					delete objectlist[i];
					objectlist.erase(objectlist.begin()+i);
					i--;
				}
				i++;
			}
		}

		if (ticksFromBegin % 400 == 267) {
			int special = 300 - 10 * level;
			int T = std::max(100, special);
				Actor* temp = new SonarKit(0, 0, 3*T, this);
				SpawnConsumable(temp);
				objectlist.push_back(temp);

		}
		if (ticksFromBegin % 365 == 146) {
			int special = 300 - 10 * level;
			int T = std::max(100, special);
			Actor* temp = new WaterPool(0, 0, T, this);
			SpawnConsumable(temp);
			objectlist.push_back(temp);

		}

		// If all the Barrels are found end the level
		if (player->foundBarrels() == TotalBarrels) {
			setTicks(0);
			playSound(SOUND_FINISHED_LEVEL);
			return GWSTATUS_FINISHED_LEVEL;
		}

		

		// Update text
		setGameStatText(MakeHeader(player->getHealth(), player->getSquirts(), player->getGold(), TotalBarrels-player->foundBarrels(), player->getSonars()));
		setTicks(getTicks() + 1);
		return GWSTATUS_CONTINUE_GAME;
	}

}

void StudentWorld::SpawnBoulder(Actor * act)
{
	int locationX;
	int locCodeY;
	coordinateGen(locationX, locCodeY);


	act->moveTo(locationX, locCodeY);
	for (int i = 0; i < objectlist.size(); i++) {
		if (act == objectlist[i])
			continue;
		if (act->tooClose(objectlist[i])) {
			coordinateGen(locationX, locCodeY);
			act->moveTo(locationX, locCodeY);

			i = 0;
		}
	}

	act->setVisible(true);


}
void StudentWorld::SpawnGoldOil(Actor * act)
{
	int locationX;
	int locCodeY;
	coordinateGen(locationX, locCodeY);


	act->moveTo(locationX, locCodeY);
	for (int i = 0; i < objectlist.size(); i++) {
		if (act == objectlist[i])
			continue;
		if (act->tooClose(objectlist[i])) {
			coordinateGen(locationX, locCodeY);
			act->moveTo(locationX, locCodeY);

			i = 0;
		}
	}

	act->setVisible(false);


}

void StudentWorld::SpawnConsumable(Actor * act)
{
	int locationX;
	int locCodeY;
	coordinateGenEmpty(locationX, locCodeY);


	act->moveTo(locationX, locCodeY);
	/*for (int i = 0; i < 64; i++) 
	for(int j=0;j<64;j++){
		if (earth[i][j]->tooClose(act))
		{
			i = 0;
			j = 0;
			coordinateGenEmpty(locationX, locCodeY);
			act->moveTo(locationX, locCodeY);
		}
	}*/

	act->setVisible(true);

}


void StudentWorld::coordinateGen(int & x, int & y)
{
	int locationX = rand() % 2;
	int locCodeY = rand() % 13;

	switch (locationX)
	{
	case 0: locationX = rand() % 26; break;
	case 1: locationX = (rand() % 26) + 35;	break;
	
	}

	switch (locCodeY)
	{
	case 0: locCodeY = 50; break;
	case 1: locCodeY = 53;	break;
	case 2: locCodeY = 49;	break;
	case 3: locCodeY = 45;	break;
	case 4: locCodeY = 41;	break;
	case 5: locCodeY = 37;	break;
	case 6: locCodeY = 33;	break;
	case 7: locCodeY = 29;	break;
	case 8: locCodeY = 25;	break;
	case 9: locCodeY = 21;	break;
	case 10: locCodeY = 17;	break;
	case 11: locCodeY = 13;	break;
	case 12: locCodeY = 8;	break;
	case 13: locCodeY = 4;	break;

	}
	x = locationX;
	y = locCodeY;
}

void StudentWorld::coordinateGenEmpty(int & x, int & y)
{
	int state = rand() % 2;
	int locationX = rand() % 4+60;
	int locCodeY = rand() % 2;
	
	
	switch (state)
	{
	case 0: locationX = rand() % 60; locCodeY =60 ; break;
	case 1: locationX = 26; locCodeY=(rand()%56)+4;	break;

	}


	x = locationX;
	y = locCodeY;
}

int StudentWorld::getTicks() const
{
	return ticksFromBegin;
}

void StudentWorld::setTicks(int a)
{
	ticksFromBegin = a;
}

void StudentWorld::SpawnObject(Actor * a){
	objectlist.push_back(a);
}

void StudentWorld::dig()
{
	if (earth[player->getX()][player->getY()]->visible == true||
	earth[player->getX() + 1][player->getY()]->visible == true ||
	earth[player->getX() + 2][player->getY()]->visible == true ||
	earth[player->getX() + 3][player->getY()]->visible == true ||

	earth[player->getX()][player->getY() + 1]->visible == true ||
	earth[player->getX() + 1][player->getY() + 1]->visible == true ||
	earth[player->getX() + 2][player->getY() + 1]->visible == true ||
	earth[player->getX() + 3][player->getY() + 1]->visible == true ||

	earth[player->getX()][player->getY() + 2]->visible == true ||
	earth[player->getX() + 1][player->getY() + 2]->visible == true ||
	earth[player->getX() + 2][player->getY() + 2]->visible == true ||
	earth[player->getX() + 3][player->getY() + 2]->visible == true ||

	earth[player->getX()][player->getY() + 3]->visible == true ||
	earth[player->getX() + 1][player->getY() + 3]->visible == true ||
	earth[player->getX() + 2][player->getY() + 3]->visible == true ||
	earth[player->getX() + 3][player->getY() + 3]->visible == true  ) {
		earth[player->getX()][player->getY()]->setVisible(false);
		earth[player->getX() + 1][player->getY()]->setVisible(false);
		earth[player->getX() + 2][player->getY()]->setVisible(false);
		earth[player->getX() + 3][player->getY()]->setVisible(false);

		earth[player->getX()][player->getY() + 1]->setVisible(false);
		earth[player->getX() + 1][player->getY() + 1]->setVisible(false);
		earth[player->getX() + 2][player->getY() + 1]->setVisible(false);
		earth[player->getX() + 3][player->getY() + 1]->setVisible(false);

		earth[player->getX()][player->getY() + 2]->setVisible(false);
		earth[player->getX() + 1][player->getY() + 2]->setVisible(false);
		earth[player->getX() + 2][player->getY() + 2]->setVisible(false);
		earth[player->getX() + 3][player->getY() + 2]->setVisible(false);

		earth[player->getX()][player->getY() + 3]->setVisible(false);
		earth[player->getX() + 1][player->getY() + 3]->setVisible(false);
		earth[player->getX() + 2][player->getY() + 3]->setVisible(false);
		earth[player->getX() + 3][player->getY() + 3]->setVisible(false);
		earth[player->getX()][player->getY()]->visible = false;
		earth[player->getX() + 1][player->getY()]->visible = false;
		earth[player->getX() + 2][player->getY()]->visible = false;
		earth[player->getX() + 3][player->getY()]->visible = false;

		earth[player->getX()][player->getY() + 1]->visible = false;
		earth[player->getX() + 1][player->getY() + 1]->visible = false;
		earth[player->getX() + 2][player->getY() + 1]->visible = false;
		earth[player->getX() + 3][player->getY() + 1]->visible = false;

		earth[player->getX()][player->getY() + 2]->visible = false;
		earth[player->getX() + 1][player->getY() + 2]->visible = false;
		earth[player->getX() + 2][player->getY() + 2]->visible = false;
		earth[player->getX() + 3][player->getY() + 2]->visible = false;

		earth[player->getX()][player->getY() + 3]->visible = false;
		earth[player->getX() + 1][player->getY() + 3]->visible = false;
		earth[player->getX() + 2][player->getY() + 3]->visible = false;
		earth[player->getX() + 3][player->getY() + 3]->visible = false;
	    playSound(SOUND_DIG);
	}
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

	//Deleting the Player
	delete player;

}


	







