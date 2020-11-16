#include "PowerUpVector.h"

void initPWUVector(PowerUpVector* vector)
{
	vector->size = 0;
	vector->capacity = 10;
	vector->pwus = new PowerUp[vector->capacity];
}

void push_backPowerUp(PowerUpVector* vector, PowerUp pwu)
{
	if (vector->size < vector->capacity)
	{
		vector->pwus[vector->size++] = pwu;
	}
	else
	{
		vector->capacity += 5;
		PowerUp* newArray = new PowerUp[vector->capacity];
		for (int i = 0; i < vector->size; i++) newArray[i] = vector->pwus[i];
		delete[] vector->pwus;
		vector->pwus = newArray;
		push_backPowerUp(vector, pwu);
	}
}

void erasePowerUp(PowerUpVector* vector, int pos)
{
	if (vector->size != 0)
	{
		if (vector->capacity > 10) vector->capacity--;
		PowerUp* newArray = new PowerUp[vector->capacity];
		int iter = 0;
		for (int i = 0; i < pos; i++) newArray[iter++] = vector->pwus[i];
		for (int i = pos + 1; i < vector->size; i++) newArray[iter++] = vector->pwus[i];
		delete[] vector->pwus;
		vector->pwus = newArray;
		vector->size--;
	}
}

void deleteVector(PowerUpVector* vector)
{
	delete[] vector->pwus;
}