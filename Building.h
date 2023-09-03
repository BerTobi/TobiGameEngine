#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include <iostream>

class Building : public Entity
{
public:
	Building();

	void setHealth(int newHealth);

	int getHealth();

protected:

	int nHealth;

};

#endif