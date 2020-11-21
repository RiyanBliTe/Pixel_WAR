#ifndef ENEMYVECTOR_H
#define ENEMYVECTOR_H

#include "Enemy.h"

/// Structure for enemies.
struct EnemyVector
{
    int size;
    int capacity;
    Enemy* enemies;
};

/// Set initial values and allocate memory for enemies vector.
/// \param vector - reference to the EnemyVector structure
void initEnemiesVector(EnemyVector* vector);

/// Add new enemy structure to the vector.
/// \param vector - reference to the EnemyVector structure
/// \param enemy - new Enemy structure
void push_backEnemy(EnemyVector* vector, Enemy enemy);

/// Delete enemy structure from the vector in position.
/// \param vector - reference to the EnemyVector structure
/// \param pos - position need to remove
void eraseEnemy(EnemyVector* vector, int pos);

/// Free vector memory.
/// \param vector - reference to the EnemyVector structure
void deleteVector(EnemyVector* vector);

#endif // !ENEMYVECTOR_H