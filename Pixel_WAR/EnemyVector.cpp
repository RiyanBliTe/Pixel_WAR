#include "EnemyVector.h"

void initEnemiesVector(EnemyVector* vector)
{
	vector->size = 0;
	vector->capacity = 10;
	vector->enemies = new Enemy[vector->capacity];
}

void push_backEnemy(EnemyVector* vector, Enemy enemy)
{
	if (vector->size < vector->capacity)
	{
		vector->enemies[vector->size++] = enemy;
	}
	else
	{
		vector->capacity += 5;
		Enemy* newArray = new Enemy[vector->capacity];
		for (int i = 0; i < vector->size; i++) newArray[i] = vector->enemies[i];
		delete[] vector->enemies;
		vector->enemies = newArray;
		push_backEnemy(vector, enemy);
	}
}

void eraseEnemy(EnemyVector* vector, int pos)
{
	if (vector->size != 0)
	{
		if (vector->capacity > 10) vector->capacity--;
		Enemy* newArray = new Enemy[vector->capacity];
		int iter = 0;
		for (int i = 0; i < pos; i++) newArray[iter++] = vector->enemies[i];
		for (int i = pos + 1; i < vector->size; i++) newArray[iter++] = vector->enemies[i];
		delete[] vector->enemies;
		vector->enemies = newArray;
		vector->size--;
	}
}

void deleteVector(EnemyVector* vector)
{
	delete[] vector->enemies;
}