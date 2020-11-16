#ifndef ENEMYVECTOR_H
#define ENEMYVECTOR_H

#include "Enemy.h"

struct EnemyVector
{
	int size;
	int capacity;
	Enemy* enemies;
};

void initEnemiesVector(EnemyVector* vector);
void push_backEnemy(EnemyVector* vector, Enemy bullet);
void eraseEnemy(EnemyVector* vector, int pos);
void deleteVector(EnemyVector* vector);

#endif // !ENEMYVECTOR_H