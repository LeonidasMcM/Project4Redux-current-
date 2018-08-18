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

bool Actor::GetStatus()
{
	return status;
}

StudentWorld *Actor::getWorld()
{
	return thisWorld;
}

void Actor::setStatus(bool input)
{
	status = input;
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

	if (health == 0)
		setStatus(false);


	// Moving Left
	if (input== KEY_PRESS_LEFT) {
		this->setDirection(left);
		if(getX()-1>0&&getX()-1<59)
		moveTo(getX() - 1, getY());
	}
	
	// Moving Left
	
	if (input==KEY_PRESS_RIGHT) {
		if (getX() + 1>0 && getX() + 1<60)
		moveTo(getX() + 1, getY());
		this->setDirection(right);
	}

	// Moving Up
	
	 if (input==KEY_PRESS_UP) {
		 if (getY() + 1>0 && getY() + 1<60)
		moveTo(getX(), getY() + 1);
		this->setDirection(up);
	}

	// Moving Down
	
	 if (input==KEY_PRESS_DOWN) {
		 if (getY() - 1>0 && getY() - 1<60)
		moveTo(getX(), getY() - 1);
		this->setDirection(down);
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
			
			 getWorld()->SpawnObject(newsquirt);
		 }
	 }

	 if (input == 'z' || input == 'Z') {
		 
		 useSonar();
	 }

}

void TunnelMan::useSonar()
{
	sonars--;
	

}

void Squirt::doSomething()
{
	if (moves == 0) {
		this->setStatus(false);
	}

	if (getDirection() == left) {
		if (getX() - 1 > 0 && getX() - 1 < 60)
		moveTo(getX() - 1, getY());
		moves--;
	}
	if (getDirection() == right) {
		if (getX() + 1>0 && getX() + 1<40)
		moveTo(getX() + 1, getY());
		moves--;
	}
	if (getDirection() == down) {
		if (getY() - 1>0 && getY() - 1<60)
		moveTo(getX() , getY()-1);
		moves--;
	}
	if (getDirection() == up) {
		if (getY() + 1>0 && getY() + 1<40)
		moveTo(getX(), getY()+1);
		moves--;
	}
}
