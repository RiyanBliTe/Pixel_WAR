#ifndef POWERUPVECTOR_H
#define POWERUPVECTOR_H

#include "PowerUp.h"

struct PowerUpVector
{
	int size;
	int capacity;
	PowerUp* pwus;
};

void initPWUVector(PowerUpVector* vector);
void push_backPowerUp(PowerUpVector* vector, PowerUp pwu);
void erasePowerUp(PowerUpVector* vector, int pos);
void deleteVector(PowerUpVector* vector);

#endif // !POWERUPVECTOR_H