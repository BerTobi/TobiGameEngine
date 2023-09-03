#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "Building.h"
#include <iostream>

class Unit : public Entity
{
public:
	Unit();

	void setHealth(int newHealth);
	void setSpeed(int newSpeed);
	void move(float nX, float nY);
	void setTarget(float nX, float nY);
	void setTargetUnit(int index);
	int getTargetUnit();
	void setTargetBuilding(int index);
	int getTargetBuilding();
	void attack(Unit* target);
	void attack(Building* target);

public:

	float fTargetX;
	float fTargetY;
	int nHealth;
	int nAttackCooldown;
	float fAttackRange;
	float fAttackDistance;

protected:

	float fSpeed;
	int nAttack;
	int nAttackSpeed;
	int nTargetUnit;
	int nTargetBuilding;


};

#endif
