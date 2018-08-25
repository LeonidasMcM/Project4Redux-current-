#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

int TunnelMan::foundBarrels()
{
	return barrels;
}



void TunnelMan::squirt()
{
	squirts--;
}

void TunnelMan::dropGold()
{
	if (gold > 0) {
		gold--;
		Actor* temp = new GoldNugget(getX(),getY(),false,getWorld());
		getWorld()->theList().push_back(temp);
	}
}

bool Actor::GetStatus()
{
	return status;
}

StudentWorld *Actor::getWorld() const
{
	return thisWorld;
}

void Actor::setStatus(bool input)
{
	status = input;
}

bool Actor::tooClose(Actor* temp)
{
	for(int i=getX()-4;i<getX()+3;i++)
		for (int j = getY() - 4; j < getY() + 3; j++) {
			if (temp->getX() == i && temp->getY() == j)
				return true;
		}
	return false;
}



int TunnelMan::getHealth()
{
	return health;
}

int TunnelMan::getSquirts()
{
	return squirts;
}

void TunnelMan::doSomething()
{
	
	int input;
	getWorld()->getKey(input);

	if (stunduration > 0) {
		stunduration--;
		return;
	}
	

	if (sonarticks > 0&&sonarstate==true)
		sonarticks--;
	if (sonarticks == 0) {
		int special = 300 - 10 * getWorld()->getLevel();
		int T = std::max(100, special);
		sonarstate = false;
		sonarticks = T;
	}




	if (health == 0)
		setStatus(false);
	vector<Actor*> boulderlist;
	for (int i = 0; i < getWorld()->theList().size(); i++) {
		if (getWorld()->theList()[i]->isBoulder())
			boulderlist.push_back(getWorld()->theList()[i]);
	}
	

	// Moving Left
	if (input== KEY_PRESS_LEFT) {
		this->setDirection(left);
	/*	if (boulderlist.size() > 0)
		{
			for (int i = 0; i < boulderlist.size(); i++) {
				if (this->getX() == boulderlist[i]->getX() + 4) {
					for (int j = boulderlist[i]->getY() - 3; i < boulderlist[i]->getY() + 3; j++)
					{
						if (getY() == j)
							return;
					}
				}
			}
			
		}
*/

		if(getX()-1>0&&getX()-1<59)
		moveTo(getX() - 1, getY());
	}
	
	// Moving Left
	
	if (input==KEY_PRESS_RIGHT) {
		this->setDirection(right);
	/*	if (boulderlist.size() > 0)
		{
			for (int i = 0; i < boulderlist.size(); i++) {
				if (this->getX() == boulderlist[i]->getX() -4) {
					for (int j = boulderlist[i]->getY() - 3; i < boulderlist[i]->getY() + 3; j++)
					{
						if (getY() == j)
							return;
					}
				}
			}

		}*/




		if (getX() + 1>0 && getX() + 1<60)
		moveTo(getX() + 1, getY());
		
	}

	// Moving Up
	
	 if (input==KEY_PRESS_UP) {
		 this->setDirection(up);
	
		 if (getY() + 1>0 && getY() + 1<60)
		moveTo(getX(), getY() + 1);
		
	}

	// Moving Down
	
	 if (input==KEY_PRESS_DOWN) {
		 this->setDirection(down);
		 if (getY() - 1>0 && getY() - 1<60)
		moveTo(getX(), getY() - 1);
		
	}

	 if (input == KEY_PRESS_SPACE) {
		 if (this->getSquirts() > 0) {
			 this->squirt();
			
			 Squirt *newsquirt=new Squirt(this->getX(),this->getY(),this->getDirection(),this->getWorld());
			 if (getDirection() == left) {
				 newsquirt->moveTo(getX() -4, getY());
			 }
			 else if(getDirection() == right) {
				 newsquirt->moveTo(getX() + 7, getY());
			 }
			 else if (getDirection() == up) {
				 newsquirt->moveTo(getX(), getY() + 7); 
			 }
			 else if (getDirection() == down) {
				 newsquirt->moveTo(getX(), getY() - 4);
			 }
			 getWorld()->playSound(SOUND_PLAYER_SQUIRT);
			 getWorld()->SpawnObject(newsquirt);
		 }
	 }

	 if (input == 'z' || input == 'Z') {
		 if (sonars > 0) {
			 useSonar();
			 getWorld()->playSound(SOUND_SONAR);
		 }
	 }

	 if (input == '\t') {
		 dropGold();

	 }
}

void TunnelMan::useSonar()
{
	if (sonars > 0) {
		sonarstate = true;
		sonars--;
	}
	

}

void Squirt::doSomething()
{
	if (moves == 0) {
		this->setStatus(false);
	}

	if (getDirection() == left) {
	/*	if (getWorld()->earth[getX() - 1][getY()]->tooClose(this) || getWorld()->earth[getX() - 1][getY() + 1]->tooClose(this) || getWorld()->earth[getX() - 1][getY() + 2]->tooClose(this) || getWorld()->earth[getX() - 1][getY() + 3]->tooClose(this)) {
			setStatus(false);
			getWorld()->playSound(SOUND_PLAYER_SQUIRT);
			return;
		}*/


		if (getX() - 1 > 0 && getX() - 1 < 60)
		moveTo(getX() - 1, getY());
		moves--;
	}
	if (getDirection() == right) {
	/*	if (getWorld()->earth[getX() + 1][getY()]->tooClose(this) || getWorld()->earth[getX() + 1][getY() + 1]->tooClose(this) || getWorld()->earth[getX() + 1][getY() + 2]->tooClose(this) || getWorld()->earth[getX() + 1][getY() + 3]->tooClose(this)) {
			setStatus(false);
			getWorld()->playSound(SOUND_PLAYER_SQUIRT);
			return;
		}*/
		if (getX() + 1>0 && getX() + 1<40)
		moveTo(getX() + 1, getY());
		moves--;
	}
	if (getDirection() == down) {
	/*	if (getWorld()->earth[getX()][getY()-1]->tooClose(this) || getWorld()->earth[getX()+1][getY()-1]->tooClose(this) || getWorld()->earth[getX() +2][getY() -1]->tooClose(this) || getWorld()->earth[getX() +3][getY() -1]->tooClose(this)) {
			setStatus(false);
			getWorld()->playSound(SOUND_PLAYER_SQUIRT);
			return;
		}*/
		if (getY() - 1>0 && getY() - 1<60)
		moveTo(getX() , getY()-1);
		moves--;
	}
	if (getDirection() == up) {
	/*	if (getWorld()->earth[getX()][getY() + 1]->tooClose(this) || getWorld()->earth[getX() + 1][getY() + 1]->tooClose(this) || getWorld()->earth[getX() + 2][getY() + 1]->tooClose(this) || getWorld()->earth[getX() + 3][getY() + 1]->tooClose(this)) {
			setStatus(false);
			getWorld()->playSound(SOUND_PLAYER_SQUIRT);
			return;
		}*/
		if (getY() + 1>0 && getY() + 1<40)
		moveTo(getX(), getY()+1);
		moves--;
	}
}

bool Boulder::IsStable()
{
	if (getWorld()->earth[getX()][getY() - 1]->visible || getWorld()->earth[getX() + 1][getY() - 1]->visible ||
		getWorld()->earth[getX() + 2][getY() - 1]->visible || getWorld()->earth[getX() + 3][getY() - 1]->visible)
	  return true;
	else
		return false;
}



void Boulder::doSomething()
{
	if (!IsStable() && !initialchange) {
		initialchange = true;
		Stability = false;
		getWorld()->playSound(SOUND_FALLING_ROCK);
		return;
	}
	if (ticks != 0 && Stability == false && initialchange == true&&!IsStable()) {
		moveTo(getX(), getY() - 1);
		if (tooClose(getWorld()->thePlayer())) {
			getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
			getWorld()->thePlayer()->setHealth(0);
		}
		return;
	}
	if (ticks != 0 && initialchange == true && IsStable()) {
		ticks--;
		if (ticks == 0)
			setStatus(false);

	}
}

bool GoldNugget::tooClose(Actor *)
{
	TunnelMan* temp = getWorld()->thePlayer();
	for (int i = getX() - 3; i<getX() + 4; i++)
		for (int j = getY() - 3; j < getY() + 4; j++) {
			if (temp->getX() == i && temp->getY() == j) {
				
					
					getWorld()->thePlayer()->foundGold();
					getWorld()->playSound(SOUND_GOT_GOODIE);
					setStatus(false);
					getWorld()->increaseScore(100);
				return true;
			}

		}
	return false;

}

void GoldNugget::sighted()
{
	TunnelMan* temp = getWorld()->thePlayer();
	if (!temp->sonarStatus())
		for (int i = getX() - 7; i<getX() + 8; i++)
			for (int j = getY() - 7; j < getY() + 8; j++) {
				if (temp->getX() == i && temp->getY() == j) {
					setVisible(true);
				}
			}
	else
		for (int i = getX() - 15; i<getX() + 16; i++)
			for (int j = getY() - 15; j < getY() + 16; j++) {
				if (temp->getX() == i && temp->getY() == j) {
					setVisible(true);
				}
			}
}

void GoldNugget::doSomething()
{
		sighted();
		tooClose(getWorld()->thePlayer());
	
}

bool Barrel::tooClose(Actor* temp)
{
	for (int i = getX() - 3; i<getX() + 4; i++)
		for (int j = getY() - 3; j < getY() + 4; j++) {
			if (temp->getX() == i && temp->getY() == j) {
				if (temp == getWorld()->thePlayer()) {
					setVisible(true);
					getWorld()->thePlayer()->foundBarrel();
					getWorld()->playSound(SOUND_FOUND_OIL);
					setStatus(false);
					getWorld()->increaseScore(500);
				}

				return true;
			}
				
		}
	return false;
	
}

void Barrel::sighted()
{
	TunnelMan* temp = getWorld()->thePlayer();
	if(!temp->sonarStatus())
	for (int i = getX() - 7; i<getX() + 8; i++)
		for (int j = getY() - 7; j < getY() + 8; j++) {
			if (temp->getX() == i && temp->getY() == j) {
				setVisible(true);
			}
		}
	else
		for (int i = getX() - 15; i<getX() + 16; i++)
			for (int j = getY() - 15; j < getY() + 16; j++) {
				if (temp->getX() == i && temp->getY() == j) {
					setVisible(true);
				}
			}
	
}

void Barrel::doSomething()
{
	sighted();
	tooClose(getWorld()->thePlayer());
}

bool Earth::tooClose(Actor *act)
{
	for (int i = getX() - 3; i < getX() + 4; i++)
		for (int j = getY() - 3; j < getY() + 4; j++)
			if (act->getX() == i && act->getY() == j)
				return true;


	return false;
}

void Consumable::tickDec()
{
	ticks--;
}

void SonarKit::doSomething()
{
	if (getTicks() > 0)
	{
		tickDec();
		if (tooClose(getWorld()->thePlayer())) {
			setStatus(false);
			getWorld()->increaseScore(50);
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->thePlayer()->incSonars();
		}

	}
	else
		setStatus(false);

}

void WaterPool::doSomething()
{
	if (getTicks() > 0)
	{
		tickDec();
		if (tooClose(getWorld()->thePlayer())) {
			setStatus(false);
			getWorld()->increaseScore(50);
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->thePlayer()->incWater();
			return;
		}

	}
	else if(getTicks()==0)
		setStatus(false);
	return;



}
