#include "Building.h"
#include "Entity.h"

Building::Building()
{
	nHealth = 0;
	nTeam = 0;
}

void Building::setHealth(int newHealth)
{
	nHealth = newHealth;
}

int Building::getHealth()
{
	return nHealth;
}
