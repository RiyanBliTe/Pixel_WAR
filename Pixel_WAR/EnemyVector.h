#ifndef ENEMYVECTOR_H
#define ENEMYVECTOR_H

#include "Enemy.h"

/// <summary>
/// Structure for enemies.
/// </summary>
struct EnemyVector
{
    int size;
    int capacity;
    Enemy* enemies;
};

/// <summary>
/// Set initial values and allocate memory for enemies vector.
/// </summary>
/// <param name="vector"> - reference to the EnemyVector structure</param>
void initEnemiesVector(EnemyVector* vector);

/// <summary>
/// Add new enemy structure to the vector.
/// </summary>
/// <param name="vector"> - reference to the EnemyVector structure</param>
/// <param name="enemy"> - new Enemy structure</param>
void push_backEnemy(EnemyVector* vector, Enemy enemy);

/// <summary>
/// Delete enemy structure from the vector in position.
/// </summary>
/// <param name="vector"> - reference to the EnemyVector structure</param>
/// <param name="pos"> - position need to remove</param>
void eraseEnemy(EnemyVector* vector, int pos);

/// Free vector memory.
/// \param vector - reference to the EnemyVector structure

/// <summary>
/// Free vector memory.
/// </summary>
/// <param name="vector"> - reference to the EnemyVector structure</param>
void deleteVector(EnemyVector* vector);

#endif // !ENEMYVECTOR_H